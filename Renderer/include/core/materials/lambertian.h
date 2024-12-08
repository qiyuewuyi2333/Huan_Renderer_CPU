#pragma once

#include "core/intersection.h"
#include "core/material.h"
#include "math/vec.h"
namespace huan_renderer_cpu
{

class Lambertian : public Material
{
  public:
    Lambertian(const math::vec3<double>& albedo) : m_albedo(albedo)
    {
    }
    Lambertian(Lambertian&&) = default;
    Lambertian(const Lambertian&) = default;
    Lambertian& operator=(Lambertian&&) = default;
    Lambertian& operator=(const Lambertian&) = default;
    ~Lambertian() = default;
    virtual Ray scatter(const Ray& ray_in, const Intersection& rec, math::vec3<double>& attenuation) const override;

  private:
    math::vec3<double> m_albedo;
};

} // namespace huan_renderer_cpu
