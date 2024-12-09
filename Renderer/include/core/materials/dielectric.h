#pragma once

#include "core/material.h"
namespace huan_renderer_cpu
{
class Dielectric : public Material
{

  public:
    Dielectric(double refrection_index);
    virtual Ray scatter(const Ray& in_ray, const Intersection& rec, math::vec3<double>& attenuation) const;

  private:
    double m_refraction_index;
};
} // namespace huan_renderer_cpu
