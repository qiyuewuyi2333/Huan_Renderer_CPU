#include "core/application.h"
#include "core/ray.h"
#include "functional/log/logger.h"
#include "functional/utils/image/image_generator.h"
#include <atomic>
#include <memory>
#include "math/vec.h"
#include "primitives/sphere.h"

namespace huan_renderer_cpu
{

void Application::render()
{
    if (m_render_setting.render_model == "diffuse")
    {
        render_diffuse();
        return;
    }
    else
    {
        render_normal();
    }
}
void Application::render_normal()
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

void Application::render_anti_aliasing()
{

    m_thread_pool->parallel_for(m_image->get_width(), m_image->get_height(), [&](uint32_t x, uint32_t y) {
        double percent_blue = 1.0 - static_cast<double>(y) / m_image->get_height();

        huan_renderer_cpu::math::vec3<double> target_color{0.0, 0.0, 0.0};
        for (int i = 0; i < m_render_setting.sample_count; ++i)
        {
            auto ray = m_camera->generate_ray_random_sample({static_cast<double>(x), static_cast<double>(y)});
            auto result = m_scene.intersect(ray, {0, 10000});
            if (result.has_value())
            {
                target_color += ((result.get_normal() + huan_renderer_cpu::math::vec3<double>{1, 1, 1}) / 2);
            }
            else
            {
                target_color += huan_renderer_cpu::math::vec3{0.53, 0.8, 0.92} * percent_blue +
                                huan_renderer_cpu::math::vec3{1.0, 1.0, 1.0} * (1.0f - percent_blue);
            }
        }
        target_color *= m_render_setting.sample_scale;
        m_image->set_pixel(x, y, target_color);
    });
    m_thread_pool->wait();
}
math::vec3<double> Application::trace_ray(const Ray& ray, int depth)
{
    if (depth <= 0)
    {
        return {0.0, 0.0, 0.0};
    }
    auto result = m_scene.intersect(ray, {0.001, 10000});

    if (result.has_value())
    {
        math::vec3<double> new_dir = result.get_normal() + math::random_unit_vector();
        return 0.5 * trace_ray(Ray(result.get_intersect_point(), new_dir), depth - 1);
    }

    math::vec3<double> unit_direction = ray.direction.normalized();
    auto blue_percent = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - blue_percent) * math::vec3<double>{1.0, 1.0, 1.0} +
           blue_percent * math::vec3<double>{0.53, 0.8, 0.92};
}

void Application::render_diffuse()
{
    std::atomic<int> finish = 0;
    m_thread_pool->parallel_for(m_image->get_width(), m_image->get_height(), [&](uint32_t x, uint32_t y) {
        huan_renderer_cpu::math::vec3<double> target_color{0.0, 0.0, 0.0};
        for (int i = 0; i < m_render_setting.sample_count; ++i)
        {
            auto ray = m_camera->generate_ray_random_sample({static_cast<double>(x), static_cast<double>(y)});
            target_color += trace_ray(ray, m_render_setting.max_bounce_depth) * m_render_setting.sample_scale;
        }
        m_image->set_pixel(x, y, target_color);
        finish++;
        if (finish % 1000 == 0)
        {
            functional::Logger::get_instance()->info(
                std::string("Progress: " + std::to_string(double(finish) / m_render_setting.pixel_total_num * 100) +
                            " % pixels rendered.")
                    .data());
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
