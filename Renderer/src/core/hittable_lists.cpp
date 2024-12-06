
#include "core/hittable_lists.h"
#include "math/interval.h"

namespace huan_renderer_cpu
{

Intersection HittableLists::intersect(const Ray& ray, const math::Interval& interval) const
{
    for (auto object : objects)
    {
        auto inter = object->intersect(ray, interval);
        if (inter.has_value())
            return inter;
    }
    return {};
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
