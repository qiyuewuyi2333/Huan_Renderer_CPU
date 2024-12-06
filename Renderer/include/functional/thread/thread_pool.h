#pragma once

#include "functional/thread/task.h"
#include "spin_lock.h"
#include <functional>
#include <queue>
#include <vector>
#include <thread>

namespace huan_renderer_cpu
{
namespace functional
{
class ThreadPool
{
  public:
    static void worker(ThreadPool* pool);

    ThreadPool(uint16_t num_threads = 0);
    ~ThreadPool();

    void parallel_for(uint32_t width, uint32_t height, const std::function<void(uint32_t, uint32_t)>& func);
    void add_task(Task* task);
    void wait();
    Task* get_task();

  private:
    std::atomic<bool> isAlive;
    std::vector<std::thread> threads;
    std::queue<Task*> tasks;
    SpinLock lock;
};

} // namespace functional
} // namespace huan_renderer_cpu
