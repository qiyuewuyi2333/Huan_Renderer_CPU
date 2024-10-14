#pragma once

#include "functional/thread/task.h"
#include <list>
#include <mutex>
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

    void add_task(Task* task);
    Task* get_task();
    private:
    bool isAlive;
    std::vector<std::thread> threads;
    std::list<Task* > tasks;
    std::mutex lock;
};

} // namespace Functional
} // namespace DRenderer