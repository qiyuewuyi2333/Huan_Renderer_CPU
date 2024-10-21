#include "functional/thread/thread_pool.h"
#include "functional/thread/parallel_task.h"
#include <algorithm>

namespace huan_renderer_cpu
{
namespace functional
{

ThreadPool::ThreadPool(uint16_t num_threads)
{
    isAlive = true;
    if (num_threads == 0)
    {
        num_threads = std::thread::hardware_concurrency();
    }
    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(std::thread(&ThreadPool::worker, this));
    }
}

ThreadPool::~ThreadPool()
{
    while (!tasks.empty())
    {
        std::this_thread::yield();
    }
    isAlive = false;
    for (auto& t : threads)
    {
        t.join();
    }
    threads.clear();
}

void ThreadPool::worker(ThreadPool* pool)
{
    while (pool->isAlive)
    {
        Task* task = pool->get_task();
        if (task)
        {
            task->run();
            delete task;
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

Task* ThreadPool::get_task()
{
    Guard guard(lock);
    if (tasks.empty())
    {
        return nullptr;
    }
    Task* task = tasks.front();
    tasks.pop();
    return task;
}

void ThreadPool::add_task(Task* task)
{
    Guard guard(lock);
    tasks.push(task);
}
void ThreadPool::wait()
{
    while (!tasks.empty())
    {
        std::this_thread::yield();
    }
}

void ThreadPool::parallel_for(uint32_t width, uint32_t height,const std::function<void(uint32_t, uint32_t)>& func)
{
    Guard guard(lock);
    for (size_t x = 0; x < width; x++)
    {
        for (size_t y = 0; y < height; y++)
        {
            tasks.push(new ParallelTask(x, y, func));
        }
    }
}

} // namespace functional
} // namespace huan_renderer_cpu
