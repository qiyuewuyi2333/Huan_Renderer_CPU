#include "functional/thread/thread_pool.h"
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
    std::unique_lock<std::mutex> guard(lock);
    if (tasks.empty())
    {
        return nullptr;
    }
    Task* task = tasks.front();
    tasks.pop_front();
    return task;
}

void ThreadPool::add_task(Task* task)
{
    std::unique_lock<std::mutex> guard(lock);
    tasks.push_back(task);
}

} // namespace functional
} // namespace huan_renderer_cpu
