#pragma once

#include "core/ray.h"
#include "math/vec.h"

namespace huan_renderer_cpu
{

class Intersection
{

  public:
    Intersection() : m_has_value(false)
    {
    }
    Intersection(const math::vec3<double>& intersect_point, const math::vec3<double>& normal)
        : m_intersect_point(intersect_point), m_normal(normal), m_has_value(true)
    {
    }

    inline bool has_value()
    {
        return m_has_value;
    }
    inline const math::vec3<double>& get_normal()
    {
        return m_normal;
    }
    inline const math::vec3<double>& get_intersect_point() const
    {
        return m_intersect_point;
    }

    inline void set_face_normal(const Ray& ray, const math::vec3<double>& outward_normal)
    {
        m_hit_front_face = ray.direction.dot(outward_normal) < 0;
        m_normal = m_hit_front_face ? outward_normal : -outward_normal;
    }

  private:
    bool m_has_value;
    bool m_hit_front_face = false;
    math::vec3<double> m_intersect_point;
    math::vec3<double> m_normal;
};
} // namespace huan_renderer_cpu
