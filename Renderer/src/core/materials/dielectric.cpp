#include "core/materials/dielectric.h"
#include "functional/utils/random.h"

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

    math::vec3<double> direction;

    double cos_theta = fmin(rec.get_normal().dot(-unit_direction), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    bool cannot_refract = ri * sin_theta > 1.0;

    if (cannot_refract || reflectance(cos_theta, m_refraction_index) > random_double())
    {
        direction = reflect(unit_direction, rec.get_normal());
    }
    else
    {
        direction = refract(unit_direction, rec.get_normal(), ri);
    }

    // return the out ray
    return {rec.get_intersect_point(), direction};
}
double Dielectric::reflectance(double cosine, double refraction_index)
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

} // namespace huan_renderer_cpu
