#pragma once

#include "math/vec.h"
namespace huan_renderer_cpu
{

struct Ray
{
    math::vec3 origin;
    math::vec3 direction;
    math::vec3 at(float t)
    {
        return origin + direction * t;
    }
    math::vec3 at(float t) const
    {
        return origin + direction * t;
    }
};

} // namespace huan_renderer_cpu
