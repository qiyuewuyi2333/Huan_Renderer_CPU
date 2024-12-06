#include "core/camera.h"
#include "functional/utils/image/random.h"
#include "math/vec.h"

namespace huan_renderer_cpu
{

/**
 * @brief Construct a new Camera:: Camera object
 *        Use original view_port_height and image parameters to define the port_width
 *
 * @param image
 * @param type
 * @param pos
 * @param view_point
 */
Camera::Camera(std::shared_ptr<huan_renderer_cpu::functional::Image> image, CameraType type,
               const math::vec3<double>& pos, const math::vec3<double>& view_point)
    : m_image(image), m_type(type), m_pos(pos), m_view_point(view_point), m_world_up({0.0f, 1.0f, 0.0f}),
      viewport_width(viewport_height * (static_cast<double>(m_image->get_width()) / m_image->get_height())),
      m_up({0.0f, 1.0f, 0.0f})
{
    m_fov = 90.0f;
    m_aspect = static_cast<double>(m_image->get_width()) / static_cast<double>(m_image->get_height());
    viewport_u = math::vec3<double>(viewport_width, 0, 0);
    viewport_v = math::vec3<double>(0, -viewport_height, 0);
    pixel_delta_u = viewport_u / static_cast<double>(m_image->get_width());
    pixel_delta_v = viewport_v / static_cast<double>(m_image->get_height());
    // Calculate the first pixel for view port, which is the uper-left from the view of camera
    viewport_upper_left = m_pos - math::vec3<double>(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Ray Camera::generate_ray(const math::vec2<double>& pixel_coord, const math::vec2<double>& offset) const
{
    auto i = pixel_coord.x + offset.x;
    auto j = pixel_coord.y + offset.y;
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto ray_direction = pixel_center - m_pos;

    return {m_pos, ray_direction};
}

Ray Camera::generate_ray_random_sample(const math::vec2<double>& pixel_coord) const
{
    auto offset = sample_square();
    auto i = pixel_coord.x + offset.x;
    auto j = pixel_coord.y + offset.y;
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto ray_direction = pixel_center - m_pos;

    return {m_pos, ray_direction};
}

math::vec3<double> Camera::sample_square() const
{
    return math::vec3<double>{random_double() - 0.5, random_double() - 0.5, 0};
}
} // namespace huan_renderer_cpu
