#include "core/materials/lambertian.h"

namespace huan_renderer_cpu
{
Ray Lambertian::scatter(const Ray& ray_in, const Intersection& rec, math::vec3<double>& attenuation) const
{
    math::vec3<double> scatter_direction = rec.get_normal() + math::random_unit_vector();
    if (scatter_direction.is_near_zero()) {
        scatter_direction = rec.get_normal();
    }


    Ray scattered(rec.get_intersect_point(), scatter_direction);
    attenuation = m_albedo;
    return scattered;
}

} // namespace huan_renderer_cpu
