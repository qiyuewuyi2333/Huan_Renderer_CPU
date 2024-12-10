#pragma once
#include "core/hittable_lists.h"
#include "math/vec.h"
#include "functional/utils/image/image.h"
#include "ray.h"
#include <memory>

namespace huan_renderer_cpu
{
/**
 * @class CameraParameters
 * @brief This structure holds the parameters for the camera, including field of view, position, look-at vector, and
 * world up vector.
 *
 */
struct CameraParameters
{
    double fov = 90.0;
    math::vec3<double> pos{0, 0, 0};
    math::vec3<double> lookat{0, 0, -1};
    math::vec3<double> world_up{0, 1, 0};
};
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
           const math::vec3<double>& pos = {0.0f, 0.0f, 0.0f}, const math::vec3<double>& lookat = {0.0f, 0.0f, -1.0f});
    Camera(const CameraParameters& parameters, std::shared_ptr<huan_renderer_cpu::functional::Image>& image);

    math::vec3<double> trace_ray(const Ray& ray, int depth, const HittableLists& scene);
    Ray generate_ray(const math::vec2<double>& pixel_coord, const math::vec2<double>& offset = {0.5, 0.5}) const;
    Ray generate_ray_random_sample(const math::vec2<double>& pixel_coord) const;
    math::vec3<double> sample_square() const;

  private:
    std::shared_ptr<huan_renderer_cpu::functional::Image> m_image;
    CameraType m_type = Camera::CameraType::Perspective;

    /**
     * @brief Defined by degrees, you can use degrees_to_radians to transfer it
     */
    double m_fov = 90.0;
    double m_aspect;
    /**
     * @brief The focal length is the distance from the optical center of the lens to the imaging plane(viewport)
     */
    double m_focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width;

    /**
     * @brief Camera coordinate vector
     */
    math::vec3<double> m_w, m_u, m_v;

    /**
     * @brief Vector across viewport horizontal edge
     */
    math::vec3<double> viewport_u;
    /**
     * @brief Vector down viewport vertical edge
     */
    math::vec3<double> viewport_v;
    math::vec3<double> pixel_delta_u;
    math::vec3<double> pixel_delta_v;
    math::vec3<double> viewport_upper_left;
    math::vec3<double> pixel00_loc;

    math::vec3<double> m_up;
    math::vec3<double> m_lookat;
    math::vec3<double> m_world_up;
    math::vec3<double> m_pos;
};
} // namespace huan_renderer_cpu
