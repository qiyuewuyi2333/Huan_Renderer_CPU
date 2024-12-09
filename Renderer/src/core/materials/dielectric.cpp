#include "core/materials/dielectric.h"

namespace huan_renderer_cpu
{
Dielectric::Dielectric(double refraction_index) : m_refraction_index(refraction_index)
{
}
Ray Dielectric::scatter(const Ray& ray_in, const Intersection& rec, math::vec3<double>& attenuation) const
{

    attenuation = {1.0, 1.0, 1.0};
    double ri = rec.is_front_face() ? (1.0 / m_refraction_index) : m_refraction_index;

    math::vec3<double> unit_direction = ray_in.direction.normalized();
    math::vec3<double> refracted = refract(unit_direction, rec.get_normal(), ri);

    // return the out ray
    return {rec.get_intersect_point(), refracted};
}

} // namespace huan_renderer_cpu
