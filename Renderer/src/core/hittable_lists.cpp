
#include "core/hittable_lists.h"
#include "core/intersection.h"
#include "math/interval.h"

namespace huan_renderer_cpu
{

Intersection HittableLists::intersect(const Ray& ray, const math::Interval& interval) const
{
    Intersection intersection = {};
    for (auto object : objects)
    {
        auto inter = object->intersect(ray, interval);
        if (inter.has_value())
        {
            if (!intersection.has_value() || inter.get_time() < intersection.get_time())
            {
                intersection = inter;
            }
        }
    }
    return intersection;
}

void HittableLists::clear()
{
    objects.clear();
}
void HittableLists::add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

} // namespace huan_renderer_cpu
