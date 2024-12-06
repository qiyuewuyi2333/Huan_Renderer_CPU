#include "core/application.h"
#include "functional/log/logger.h"
#include "functional/utils/image/image_generator.h"
#include <memory>
#include "primitives/sphere.h"

namespace huan_renderer_cpu
{

void Application::render()
{

    // NOTE: 在多线程外访问共享变量时一定要小心，可能会存在释放的问题，总之，要小心！
    m_thread_pool->parallel_for(m_image->get_width(), m_image->get_height(), [&](uint32_t x, uint32_t y) {
        auto ray = m_camera->generate_ray({static_cast<double>(x), static_cast<double>(y)});
        double percent_blue = 1.0 - static_cast<double>(y) / m_image->get_height();

        huan_renderer_cpu::math::vec3<double> target_color{0.0, 0.0, 0.0};
        auto result = m_scene.intersect(ray, {0, 10000});
        if (result.has_value())
        {
            m_image->set_pixel(x, y, (result.get_normal() + huan_renderer_cpu::math::vec3<double>{1, 1, 1}) / 2);
        }
        else
        {
            auto tar_color =
                huan_renderer_cpu::Color(huan_renderer_cpu::math::vec3{0.53, 0.8, 0.92} * percent_blue +
                                         huan_renderer_cpu::math::vec3{1.0, 1.0, 1.0} * (1.0f - percent_blue));
            m_image->set_pixel(x, y, tar_color);
        }
    });
    m_thread_pool->wait();
}
void Application::destory()
{
}

/**
 * @brief NOTE: Initialize the application with settings
 */
void Application::initialize()
{
    initialize_instance();

    // init thread pool
    m_thread_pool = std::make_unique<functional::ThreadPool>(std::thread::hardware_concurrency());
    // init image
    m_image = std::make_shared<functional::Image>(m_render_setting.image_width, m_render_setting.image_height,
                                                  m_render_setting.aspect_ratio);
    // init camera
    m_camera = std::make_unique<huan_renderer_cpu::Camera>(m_image);

    // init scene
    primitives::Sphere sphere{{0, 0, -1}, 0.5f};
    primitives::Sphere big_sphere{{0, -100.5, -1}, 100.f};
    m_scene.add(std::make_shared<huan_renderer_cpu::primitives::Sphere>(sphere));
    m_scene.add(std::make_shared<huan_renderer_cpu::primitives::Sphere>(big_sphere));
}
void Application::initialize_instance()
{
    // init logger
    functional::Logger::create_instance();
    // inti image generator
    functional::ImageGenerator::create_instance();
}

void Application::save_image(const std::string& name)
{
    m_image_generator->save(name, m_image);
}
Application::Application()
{
    // NOTE: non-parameter constructor has been abondoned.
}

} // namespace huan_renderer_cpu
