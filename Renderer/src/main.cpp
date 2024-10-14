#include <iostream>
#include "functional/thread/task.h"
#include "functional/thread/thread_pool.h"
#include "functional/log/logger.h"
#include "core/core.h"
#include "functional/utils/image/image.h"
#include "functional/utils/image/image_generator.h"

using namespace std;
class SimpleTask : public huan_renderer_cpu::functional::Task
{
  public:
    void run() override
    {
        LOG_INFO("Hello My thread!");
    }
};
int main(int argc, char** argv)
{
    __cplusplus;
    cout << "Hello world!" << endl;
    huan_renderer_cpu::functional::ImageGenerator::create_instance();

    huan_renderer_cpu::functional::Image image(1920,1080);

    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            image.set_pixel(j, i, 1.0f, 1.0f, 0.0f);
        }
    }

    huan_renderer_cpu::functional::ImageGenerator::get_instance()->save("test.ppm", image);

    return 0;
}