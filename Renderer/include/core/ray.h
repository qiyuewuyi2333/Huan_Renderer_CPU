#pragma once

#include "math/vec.h"
namespace huan_renderer_cpu
{

struct Ray
{
    math::vec3<double> origin;
    math::vec3<double> direction;

    math::vec3<double> at(double t)
    {
        return origin + direction * t;
    }
    math::vec3<double> at(double t) const
    {
        return origin + direction * t;
    }
};

} // namespace huan_renderer_cpu
