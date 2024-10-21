#include <iostream>
#include <string>
#include "functional/thread/task.h"
#include "functional/thread/thread_pool.h"
#include "functional/log/logger.h"
#include "core/core.h"
#include "functional/utils/image/image.h"
#include "functional/utils/image/image_generator.h"
#include "primitives/sphere.h"
#include "core/camera.h"

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
    huan_renderer_cpu::functional::Logger::create_instance();
    huan_renderer_cpu::functional::ThreadPool thread_pool{};
    huan_renderer_cpu::functional::ImageGenerator::create_instance();
    // Calculate the image height, and ensure that it's at least 1.
    auto aspect_ratio = 16.0 / 9.0;
    uint32_t image_height = 1080;
    uint32_t image_width = image_height * aspect_ratio;
    std::shared_ptr<huan_renderer_cpu::functional::Image> image =
        make_shared<huan_renderer_cpu::functional::Image>(image_width, image_height);
    huan_renderer_cpu::Camera camera(image);

    // camera get pixel color for every pixel
    huan_renderer_cpu::primitives::Sphere sphere{{0, 0, -1}, 0.5f};
    huan_renderer_cpu::math::vec3 light_pos{1, 1, 1};
    thread_pool.parallel_for(image_width, image_height, [&](uint32_t x, uint32_t y) {
        auto ray = camera.generate_ray({static_cast<float>(x), static_cast<float>(y)});
        auto result = sphere.intersect(ray);
        if (result.has_value())
            image->set_pixel(x, y, {1, 0, 0});
    });
    thread_pool.wait();

    huan_renderer_cpu::functional::ImageGenerator::get_instance()->save("test.ppm", image);

    
    return 0;
}