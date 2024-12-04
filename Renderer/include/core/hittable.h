#pragma once

#include "core/intersection.h"
#include "core/ray.h"
namespace huan_renderer_cpu
{
class Hittable
{
  public:
    virtual Intersection intersect(const Ray& ray, double t_min, double t_max) const = 0;
};
} // namespace huan_renderer_cpu
