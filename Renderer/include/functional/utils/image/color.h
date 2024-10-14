#pragma once

namespace huan_renderer_cpu
{
    struct Color
    {
        float r = 0.0f, g=0.0f, b=0.0f,a = 0.0f;
        float operator[](int index)
        {
            return (&r)[index];
        }
    };
}