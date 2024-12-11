#pragma once
#include <random>
#include "math/core.h"

namespace huan_renderer_cpu
{

inline double degrees_to_radians(double degrees)
{
    return degrees * math::MY_PI / 180.0;
}

/**
 * @brief Generate a random double value, default between 0 ~ 1
 *
 * @return random double
 */
inline double random_double()
{
    // Returns a random real in [0,1).
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

/**
 * @brief Generate a random double value, default between 0 ~ 1
 *
 * @return random double
 */
inline double random_double(double min, double max)
{
    // Returns a random real in [min,max).

    static std::mt19937 generator;
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

} // namespace huan_renderer_cpu
