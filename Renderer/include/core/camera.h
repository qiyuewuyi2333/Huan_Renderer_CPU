#pragma once
#include "math/mat.h"
#include "math/vec.h"
#include "math/core.h"
#include "functional/utils/image/image.h"
#include "ray.h"
#include <memory>

namespace huan_renderer_cpu
{

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
           const math::vec3& pos = {0.0f, 0.0f, 0.0f}, const math::vec3& view_point = {0.0f, 0.0f, 0.0f});
    Ray generate_ray(const math::vec2& pixel_coord, const math::vec2& offset = {0.5, 0.5}) const;

  private:
    std::shared_ptr<huan_renderer_cpu::functional::Image> m_image;
    CameraType m_type;

    float m_fov;
    float m_aspect;
    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width;
    math::vec3 viewport_u;
    math::vec3 viewport_v;
    math::vec3 pixel_delta_u;
    math::vec3 pixel_delta_v;
    math::vec3 viewport_upper_left;
    math::vec3 pixel00_loc;

    math::vec3 m_up;
    math::vec3 m_right;
    math::vec3 m_view_point;
    math::vec3 m_world_up;
    math::vec3 m_pos;
};
} // namespace huan_renderer_cpu