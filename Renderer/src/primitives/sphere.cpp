#include "primitives/sphere.h"

namespace huan_renderer_cpu
{
namespace primitives
{
Sphere::Sphere(const math::vec3& center, float radius) : center(center), radius(radius)
{
}
std::optional<float> Sphere::intersect(const Ray& ray) const
{
    math::vec3 oc = center - ray.origin;
    auto a = ray.direction.dot(ray.direction);
    auto b = ray.direction.dot(oc);
    auto c = oc.dot(oc) - radius*radius;
    auto delta = b*b - a*c;
    if (delta < 0)
    {
        return {};
    }
    return {(b - sqrt(delta))/a};
}

} // namespace primitives

} // namespace huan_renderer_cpu