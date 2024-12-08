#include "core/materials/metal.h"
#include "math/vec.h"

namespace huan_renderer_cpu
{
Ray Metal::scatter(const Ray& ray_in, const Intersection& rec, math::vec3<double>& attenuation) const
{
    // use fuzz to increase the random value
    math::vec3<double> scatter_direction =
        math::reflect(ray_in.direction, rec.get_normal()).normalized() + m_fuzz * math::random_unit_vector();
    if (scatter_direction.dot(rec.get_normal()) < 0)
    {
        return Ray{};
    }

    Ray scattered(rec.get_intersect_point(), scatter_direction);
    attenuation = m_albedo;
    return scattered;
}

} // namespace huan_renderer_cpu
