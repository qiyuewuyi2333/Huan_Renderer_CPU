#include "primitives/sphere.h"
#include "core/intersection.h"
#include <memory>

namespace huan_renderer_cpu
{
namespace primitives
{
Sphere::Sphere(const math::vec3<double>& center, double radius, const std::shared_ptr<Material>& material)
    : center(center), radius(radius), m_material(material)
{
}

Intersection Sphere::intersect(const Ray& ray, const math::Interval& interval) const
{
    math::vec3 oc = ray.origin - center;
    auto a = ray.direction.dot(ray.direction);
    auto b = ray.direction.dot(oc);
    auto c = oc.dot(oc) - radius * radius;
    auto delta = b * b - a * c;
    if (delta < 0)
    {
        return {};
    }
    auto sqrt_delta = sqrt(delta);
    auto t1 = (-b - sqrt_delta) / a;
    if (interval.contains(t1))
    {
        auto intersection_point = ray.at(t1);
        auto normal = (intersection_point - center) / radius;
        auto inter = Intersection(t1, intersection_point, normal, m_material);
        inter.set_face_normal(ray, normal);

        return inter;
    }
    t1 = (-b + sqrt_delta) / a;
    if (interval.contains(t1))
    {
        auto intersection_point = ray.at(t1);
        auto normal = (intersection_point - center) / radius;
        auto inter = Intersection(t1, intersection_point, normal, m_material);
        inter.set_face_normal(ray, normal);

        return inter;
    }

    return {};
}

} // namespace primitives

} // namespace huan_renderer_cpu
