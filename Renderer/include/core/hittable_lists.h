#pragma once

#include "core/hittable.h"
#include "core/intersection.h"
#include "math/interval.h"
#include <memory>
#include <vector>
namespace huan_renderer_cpu
{

class HittableLists
{
  public:
    HittableLists() = default;
    HittableLists(HittableLists&&) = default;
    HittableLists(const HittableLists&) = default;
    HittableLists& operator=(HittableLists&&) = default;
    HittableLists& operator=(const HittableLists&) = default;
    ~HittableLists() = default;

    void clear();
    void add(std::shared_ptr<Hittable> object);
    Intersection intersect(const Ray& ray, const math::Interval& interval) const;

  private:
    std::vector<std::shared_ptr<Hittable>> objects;
};

} // namespace huan_renderer_cpu
