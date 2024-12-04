#pragma once
#include "core/hittable.h"
#include "core/intersection.h"
#include "math/vec.h"
#include "core/ray.h"

namespace huan_renderer_cpu
{
namespace primitives
{
class Sphere : public Hittable
{
  public:
    Sphere(const math::vec3& center, float radius);
    Intersection intersect(const Ray& ray, double t_min, double t_max) const;

  public:
    math::vec3 center;
    float radius;
};
} // namespace primitives
} // namespace huan_renderer_cpu
