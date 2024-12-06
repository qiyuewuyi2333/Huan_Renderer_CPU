#pragma once
#include "math/mat.h"
#include "math/vec.h"
#include "math/core.h"
#include "functional/utils/image/image.h"
#include "ray.h"
#include <memory>

namespace huan_renderer_cpu
{
/**
 * @brief 241027 Now it's a really simple camera, whose pos is original point and looking along with the negative z-axis
            And there is a viewport has 1.0 distance to camera, that means the viewport's center is (0,0,-1)
 *
 */
class Camera
{
  public:
    enum class CameraType
    {
        Perspective,
        Orthographic
    };
    enum class CameraMovement
    {
        Forward,
        Backward,
        Left,
        Right,
        Up,
        Down
    };
    enum class Fov
    {
        Vertical,
        Horizontal
    };
    Camera(std::shared_ptr<huan_renderer_cpu::functional::Image> image, CameraType type = CameraType::Perspective,
           const math::vec3<double>& pos = {0.0f, 0.0f, 0.0f},
           const math::vec3<double>& view_point = {0.0f, 0.0f, -1.0f});
    Ray generate_ray(const math::vec2<double>& pixel_coord, const math::vec2<double>& offset = {0.5, 0.5}) const;
    Ray generate_ray_random_sample(const math::vec2<double>& pixel_coord) const;
    math::vec3<double> sample_square() const;

  private:
    std::shared_ptr<huan_renderer_cpu::functional::Image> m_image;
    CameraType m_type;

    double m_fov;
    double m_aspect;
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width;
    math::vec3<double> viewport_u;
    math::vec3<double> viewport_v;
    math::vec3<double> pixel_delta_u;
    math::vec3<double> pixel_delta_v;
    math::vec3<double> viewport_upper_left;
    math::vec3<double> pixel00_loc;

    math::vec3<double> m_up;
    math::vec3<double> m_right;
    math::vec3<double> m_view_point;
    math::vec3<double> m_world_up;
    math::vec3<double> m_pos;
};
} // namespace huan_renderer_cpu
