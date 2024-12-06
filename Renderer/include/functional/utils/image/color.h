#pragma once
#include "math/vec.h"
#include "math/interval.h"

namespace huan_renderer_cpu
{
struct Color
{
    double r = 0.0, g = 0.0, b = 0.0, a = 0.0;
    double operator[](int index)
    {
        return (&r)[index];
    }
    Color()
    {
    }
    Color(const math::vec3<double>& c)
    {
        r = c.x;
        g = c.y;
        b = c.z;
    }
    Color(double r, double g, double b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    inline math::vec3<int> norm_color_to_255()
    {
        static const math::Interval intensity(0.000, 0.999);
        return math::vec3<int>((256 * intensity.clamp(r)), int(256 * intensity.clamp(g)),
                               int(256 * intensity.clamp(b)));
    }
};
} // namespace huan_renderer_cpu
