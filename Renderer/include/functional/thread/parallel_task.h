#pragma once
#include "functional/thread/task.h"
#include <functional>

namespace huan_renderer_cpu
{
namespace functional
{

class ParallelTask : public Task
{
    public:
    ParallelTask(uint32_t x, uint32_t y, const std::function<void(uint32_t, uint32_t)>& func) : x(x), y(y), func(func)
    {
    }
    void run() override
    {
        func(x, y);
    }

  private:
    uint32_t x, y;
    std::function<void(uint32_t, uint32_t)> func;
};
} // namespace functional

} // namespace huan_renderer_cpu