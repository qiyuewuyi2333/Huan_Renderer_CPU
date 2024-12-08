#pragma once

#include "math/vec.h"
namespace huan_renderer_cpu
{

struct Ray
{
    math::vec3<double> origin;
    math::vec3<double> direction;
    Ray() : origin(0, 0, 0), direction(0, 0, 0)
    {
    }
    Ray(const math::vec3<double>& origin, const math::vec3<double>& direction) : origin(origin), direction(direction)
    {
    }
    Ray(math::vec3<double>&& origin, math::vec3<double>&& direction)
        : origin(std::move(origin)), direction(std::move(direction))
    {
    }

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
