#pragma once

#include "core/intersection.h"
#include "core/material.h"
#include "math/vec.h"
namespace huan_renderer_cpu
{

class Metal : public Material
{
  public:
    Metal(const math::vec3<double>& albedo, double fuzz) : m_albedo(albedo), m_fuzz(fuzz > 1 ? 1 : fuzz)
    {
    }
    Metal(Metal&&) = default;
    Metal(const Metal&) = default;
    Metal& operator=(Metal&&) = default;
    Metal& operator=(const Metal&) = default;
    ~Metal() = default;
    virtual Ray scatter(const Ray& ray_in, const Intersection& rec, math::vec3<double>& attenuation) const override;

  private:
    math::vec3<double> m_albedo;
    double m_fuzz;
};

} // namespace huan_renderer_cpu
