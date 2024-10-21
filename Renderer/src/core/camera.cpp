#include "core/camera.h"

namespace huan_renderer_cpu
{
Camera::Camera(std::shared_ptr<huan_renderer_cpu::functional::Image> image, CameraType type, const math::vec3& pos,
               const math::vec3& view_point)
    : m_image(image), m_type(type), m_pos(pos), m_view_point(view_point), m_world_up({0.0f, 1.0f, 0.0f}),
      viewport_width(viewport_height * (static_cast<double>(m_image->get_width()) / m_image->get_height())),
      m_up({0.0f, 1.0f, 0.0f})
{
    m_fov = 90.0f;
    m_aspect = static_cast<float>(m_image->get_width()) / static_cast<float>(m_image->get_height());
    viewport_u = math::vec3(viewport_width, 0, 0);
    viewport_v = math::vec3(0, -viewport_height, 0);
    pixel_delta_u = viewport_u / static_cast<float>(m_image->get_width());
    pixel_delta_v = viewport_v / static_cast<float>(m_image->get_height());

    viewport_upper_left = m_pos - math::vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Ray Camera::generate_ray(const math::vec2& pixel_coord, const math::vec2& offset) const
{
    auto i = pixel_coord.x + offset.x;
    auto j = pixel_coord.y + offset.y;
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto ray_direction = pixel_center - m_pos;

    return {m_pos, ray_direction};
}

} // namespace huan_renderer_cpu