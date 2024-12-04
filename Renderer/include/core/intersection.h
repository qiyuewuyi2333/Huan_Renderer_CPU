#pragma once

#include "math/vec.h"
namespace huan_renderer_cpu
{

class Intersection
{

  public:
    Intersection() : m_has_value(false)
    {
    }
    Intersection(const math::vec3& intersect_point, const math::vec3& normal)
        : m_intersect_point(intersect_point), m_normal(normal), m_has_value(true)
    {
    }
    inline bool has_value()
    {
        return m_has_value;
    }
    inline const math::vec3& get_intersect_point() const
    {
        return m_intersect_point;
    }

  private:
    bool m_has_value;
    math::vec3 m_intersect_point;
    math::vec3 m_normal;
};
} // namespace huan_renderer_cpu
