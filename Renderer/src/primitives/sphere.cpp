#include "primitives/sphere.h"
#include "core/intersection.h"

namespace huan_renderer_cpu
{
namespace primitives
{
Sphere::Sphere(const math::vec3& center, float radius) : center(center), radius(radius)
{
}

Intersection Sphere::intersect(const Ray& ray, double t_min, double t_max) const
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
    if (t1 > t_min && t1 < t_max)
    {
        auto intersection_point = ray.at(t1);
        auto normal = (intersection_point - center) / radius;

        return Intersection(intersection_point, normal);
    }
    t1 = (-b + sqrt_delta) / a;
    if (t1 > t_min && t1 < t_max)
    {
        auto intersection_point = ray.origin + (ray.direction * t1);
        auto normal = (intersection_point - center) / radius;

        return Intersection(intersection_point, normal);
    }

    return {};
}

} // namespace primitives

} // namespace huan_renderer_cpu
