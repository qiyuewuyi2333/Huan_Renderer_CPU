#pragma once
#include "math/vec.h"
#include "core/ray.h"
#include <optional>

namespace huan_renderer_cpu
{
namespace primitives
{
class Sphere
{
    public:
    Sphere(const math::vec3& center, float radius);
    std::optional<float> intersect(const Ray& ray) const;
    
    public:

    math::vec3 center;
    float radius;

};
} // namespace primitives
} // namespace huan_renderer_cpu