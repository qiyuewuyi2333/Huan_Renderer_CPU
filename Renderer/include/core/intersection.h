#pragma once

#include "core/ray.h"
#include "math/core.h"
#include "math/vec.h"
#include <memory>

namespace huan_renderer_cpu
{

class Material;
class Intersection
{

  public:
    Intersection() : m_has_value(false)
    {
    }
    Intersection(double t, const math::vec3<double>& intersect_point, const math::vec3<double>& normal,
                 const std::shared_ptr<Material>& material)
        : m_has_value(true), m_t(t), m_intersect_point(intersect_point), m_normal(normal), m_material(material)
    {
    }

    inline bool has_value()
    {
        return m_has_value;
    }
    inline bool has_value() const
    {
        return m_has_value;
    }
    inline double get_time()
    {
        return m_t;
    }
    inline const math::vec3<double>& get_normal()
    {
        return m_normal;
    }
    inline const math::vec3<double>& get_normal() const
    {
        return m_normal;
    }
    inline const math::vec3<double>& get_intersect_point() const
    {
        return m_intersect_point;
    }
    inline const std::shared_ptr<Material>& get_material()
    {
        return m_material;
    }
    inline const std::shared_ptr<Material>& get_material() const
    {
        return m_material;
    }

    inline void set_face_normal(const Ray& ray, const math::vec3<double>& outward_normal)
    {
        m_hit_front_face = ray.direction.dot(outward_normal) < 0;
        m_normal = m_hit_front_face ? outward_normal : -outward_normal;
    }

  private:
    bool m_has_value;
    bool m_hit_front_face = false;
    double m_t = math::MY_INFINITY;
    math::vec3<double> m_intersect_point;
    math::vec3<double> m_normal;

    std::shared_ptr<Material> m_material;
};
} // namespace huan_renderer_cpu
