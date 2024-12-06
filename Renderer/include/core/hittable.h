#pragma once

#include "core/intersection.h"
#include "core/ray.h"
#include "math/interval.h"
namespace huan_renderer_cpu
{
class Hittable
{
  public:
    virtual Intersection intersect(const Ray& ray, const math::Interval& interval) const = 0;
};
} // namespace huan_renderer_cpu
