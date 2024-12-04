#include <iostream>
#include "functional/thread/task.h"
#include "functional/thread/thread_pool.h"
#include "functional/log/logger.h"
#include "core/core.h"
#include "functional/utils/image/image.h"
#include "functional/utils/image/image_generator.h"
#include "math/vec.h"
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

struct Light
{
    huan_renderer_cpu::math::vec3 light_pos{1, 1, 1};
    huan_renderer_cpu::math::vec3 light_color{1, 1, 1};
    float light_source_radius = 0.1f;
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
    huan_renderer_cpu::math::vec3 light_blue_color{0.53f, 0.8f, 0.92f};
    huan_renderer_cpu::math::vec3 white_color{1, 1, 1};

    thread_pool.parallel_for(image_width, image_height, [&](uint32_t x, uint32_t y) {
        auto ray = camera.generate_ray({static_cast<float>(x), static_cast<float>(y)});
        auto result = sphere.intersect(ray, 0, 100000);
        float percent_blue = 1 - static_cast<float>(y) / image_height;
        // make the ball in the light, so we need to calculate the shadow
        // simply, we assume there is a light ball in the scene , whose pos is 1 1 1,
        // and has the radius 0.1
        // we calculate our sight to the light ball, reflect from the sphere, and get a simple mod about lighting
        if (result.has_value())
        {
            // I have intersect point in result
            // so I can get the normal vector for every point I see
            //
            auto normal_vec = result.get_intersect_point() - sphere.center;
            image->set_pixel(x, y, (normal_vec + huan_renderer_cpu::math::vec3{1, 1, 1}) / 2);
        }
        else
            image->set_pixel(
                x, y, huan_renderer_cpu::Color(light_blue_color * percent_blue + white_color * (1 - percent_blue)));
    });
    thread_pool.wait();
    huan_renderer_cpu::functional::ImageGenerator::get_instance()->save("test.ppm", image);

    return 0;
}
