#pragma once

#include "math/core.h"
namespace huan_renderer_cpu
{
namespace math
{

class Interval
{
  public:
    Interval(double min, double max) : m_min(min), m_max(max)
    {
    }
    Interval(Interval&&) = default;
    Interval(const Interval&) = default;
    Interval& operator=(Interval&&) = default;
    Interval& operator=(const Interval&) = default;
    ~Interval() = default;

    inline bool size() const
    {
        return m_max - m_min;
    }
    inline bool contains(double x) const
    {
        return x >= m_min && x <= m_max;
    }
    inline double clamp(double x) const
    {
        if (x < m_min)
            return m_min;
        if (x > m_max)
            return m_max;
        return x;
    }

  private:
    double m_min;
    double m_max;

  public:
    static const Interval empty, universe;
};
inline const Interval Interval::empty = Interval(+MY_INFINITY, -MY_INFINITY);
inline const Interval Interval::universe = Interval(-MY_INFINITY, +MY_INFINITY);

} // namespace math

} // namespace huan_renderer_cpu
