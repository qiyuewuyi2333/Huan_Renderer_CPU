#include "core/camera.h"
#include "functional/utils/random.h"
#include "math/vec.h"
#include "core/material.h"
#include <cmath>

namespace huan_renderer_cpu
{

Camera::Camera(const CameraParameters& parameters, std::shared_ptr<huan_renderer_cpu::functional::Image>& image)
    : m_fov(parameters.fov), m_pos(parameters.pos), m_lookat(parameters.lookat), m_world_up(parameters.world_up),
      m_image(image), m_defocus_angle(parameters.defocus_angle), m_focus_dist(parameters.focus_dist)
{
    double theta = degrees_to_radians(m_fov);
    viewport_height = 2 * std::tan(theta / 2) * m_focus_dist;
    viewport_width = viewport_height * (static_cast<double>(m_image->get_width()) / m_image->get_height());

    // NOTE: Make Camera coordinate system like a Right hand coordinate system
    m_w = ((m_pos - m_lookat).normalized());
    m_u = cross(m_world_up, m_w).normalized();
    m_v = cross(m_w, m_u);

    m_aspect = static_cast<double>(m_image->get_width()) / static_cast<double>(m_image->get_height());

    viewport_u = viewport_width * m_u;     // Vector across viewport horizontal edge
    viewport_v = viewport_height * (-m_v); // Vector down viewport vertical edge
    pixel_delta_u = viewport_u / static_cast<double>(m_image->get_width());
    pixel_delta_v = viewport_v / static_cast<double>(m_image->get_height());
    // Calculate the first pixel for view port, which is the uper-left from the view of camera
    viewport_upper_left = m_pos - (m_focus_dist * m_w) - (viewport_u / 2) - (viewport_v / 2);
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius = m_focus_dist * std::tan(degrees_to_radians(m_defocus_angle / 2));
    m_defocus_disk_u = m_u * defocus_radius;
    m_defocus_disk_v = m_v * defocus_radius;
}
Ray Camera::generate_ray(const math::vec2<double>& pixel_coord, const math::vec2<double>& offset) const
{
    auto i = pixel_coord.x + offset.x;
    auto j = pixel_coord.y + offset.y;
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

    auto ray_origin = (m_defocus_angle <= 0) ? m_pos : defocus_disk_sample();
    auto ray_direction = pixel_center - ray_origin;

    return {ray_origin, ray_direction};
}

Ray Camera::generate_ray_random_sample(const math::vec2<double>& pixel_coord) const
{
    auto offset = sample_square();
    auto i = pixel_coord.x + offset.x;
    auto j = pixel_coord.y + offset.y;
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

    auto ray_origin = (m_defocus_angle <= 0) ? m_pos : defocus_disk_sample();
    auto ray_direction = pixel_center - ray_origin;

    return {ray_origin, ray_direction};
}
math::vec3<double> Camera::defocus_disk_sample() const
{
    // Returns a random point in the camera defocus disk.
    auto p = math::random_vec_in_unit_circle();
    return m_pos + (p.x * m_defocus_disk_u) + (p.y * m_defocus_disk_v);
}
math::vec3<double> Camera::trace_ray(const Ray& ray, int depth, const HittableLists& scene)
{
    if (depth <= 0)
    {
        return {0.0, 0.0, 0.0};
    }
    if (ray.direction.is_near_zero())
    {
        return math::vec3<double>{0.0, 0.0, 0.0};
    }
    const auto result = scene.intersect(ray, {0.001, 10000});

    if (result.has_value())
    {
        Material* material = result.get_material().get();
        math::vec3<double> attenuation;
        Ray new_ray = material->scatter(ray, result, attenuation);
        return attenuation * trace_ray(new_ray, depth - 1, scene);
    }

    math::vec3<double> unit_direction = ray.direction.normalized();
    auto blue_percent = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - blue_percent) * math::vec3<double>{1.0, 1.0, 1.0} +
           blue_percent * math::vec3<double>{0.53, 0.8, 0.92};
}

math::vec3<double> Camera::sample_square() const
{
    return math::vec3<double>{random_double() - 0.5, random_double() - 0.5, 0};
}
} // namespace huan_renderer_cpu
