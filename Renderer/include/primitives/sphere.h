#pragma once
#include "core/hittable.h"
#include "core/intersection.h"
#include "math/interval.h"
#include "math/vec.h"
#include "core/ray.h"
#include <memory>

namespace huan_renderer_cpu
{
namespace primitives
{
class Sphere : public Hittable
{
  public:
    Sphere(const math::vec3<double>& center, double radius, const std::shared_ptr<Material>& material);
    Intersection intersect(const Ray& ray, const math::Interval& interval) const;

  public:
    math::vec3<double> center;
    double radius;
    std::shared_ptr<Material> m_material;
};
} // namespace primitives
} // namespace huan_renderer_cpu
