#pragma once
#include <iostream>

namespace huan_renderer_cpu
{
namespace functional
{
class Task
{
    public:
    virtual void run() = 0; 
    virtual ~Task() {}
    private:
};

} 
} 