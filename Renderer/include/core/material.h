#pragma once

#include "core/intersection.h"
#include "core/ray.h"
#include "math/vec.h"
namespace huan_renderer_cpu
{

class Material
{
  public:
    Material() = default;
    Material(Material&&) = default;
    Material(const Material&) = default;
    Material& operator=(Material&&) = default;
    Material& operator=(const Material&) = default;
    ~Material() = default;

    virtual Ray scatter(const Ray& in_ray, const Intersection& rec, math::vec3<double>& attenuation) const = 0;

  private:
};

} // namespace huan_renderer_cpu
