#pragma once
#include <atomic>
#include <thread>

namespace huan_renderer_cpu
{
namespace functional
{

class SpinLock
{
  public:
    void acquire()
    {
        while (flag.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
    }
    void release()
    {
        flag.clear(std::memory_order_release);
    }

  private:
    std::atomic_flag flag{};
};
class Guard
{
  public:
    Guard(SpinLock& spin_lock) : spin_lock(spin_lock)
    {
        spin_lock.acquire();
    }
    ~Guard()
    {
        spin_lock.release();
    }

  private:
    SpinLock& spin_lock;
};
} // namespace functional
} // namespace huan_renderer_cpu