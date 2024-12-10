#include "core/application.h"
#include "core/camera.h"
#include "core/hittable_lists.h"
#include "core/material.h"
#include "core/materials/dielectric.h"
#include "core/materials/lambertian.h"
#include "core/materials/metal.h"
#include "core/ray.h"
#include "functional/log/logger.h"
#include "functional/utils/image/image_generator.h"
#include <algorithm>
#include <atomic>
#include <cmath>
#include <memory>
#include "math/core.h"
#include "math/vec.h"
#include "primitives/sphere.h"

namespace huan_renderer_cpu
{

void Application::render()
{

    render_diffuse();
}

void Application::render_diffuse()
{
    // NOTE: 在多线程外访问共享变量时一定要小心，可能会存在释放的问题，总之，要小心！
    std::atomic<int> finish = 0;
    m_thread_pool->parallel_for(m_image->get_width(), m_image->get_height(), [&](uint32_t x, uint32_t y) {
        huan_renderer_cpu::math::vec3<double> target_color{0.0, 0.0, 0.0};
        for (int i = 0; i < m_render_setting.sample_count; ++i)
        {
            auto ray = m_camera->generate_ray_random_sample({static_cast<double>(x), static_cast<double>(y)});
            target_color +=
                m_camera->trace_ray(ray, m_render_setting.max_bounce_depth, m_scene) * m_render_setting.sample_scale;
        }
        m_image->set_pixel(x, y, target_color);
        finish++;
        if (finish % 10000 == 0)
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
    functional::Logger::get_instance()->debug("ThreadPool initialized!");
    // init image
    m_image = std::make_shared<functional::Image>(m_render_setting.image_width, m_render_setting.image_height,
                                                  m_render_setting.aspect_ratio);
    // init camera
    CameraParameters camera_parameters{.fov = 90, .pos = {-2, 2, 1}, .lookat = {0, 0, -1}};
    m_camera = std::make_unique<huan_renderer_cpu::Camera>(camera_parameters, m_image);
    functional::Logger::get_instance()->debug("Camera initialized!");

    // init scene
    // Material
    HittableLists camera_test_scene;
    HittableLists material_test_scene;

    auto material_ground = std::make_shared<Lambertian>(math::vec3<double>{0.8, 0.8, 0.0});
    auto material_center = std::make_shared<Lambertian>(math::vec3<double>{0.1, 0.2, 0.5});
    auto material_left = std::make_shared<Dielectric>(1.50);
    auto material_bubble = std::make_shared<Dielectric>(1.0 / 1.50);
    auto material_right = std::make_shared<Metal>(math::vec3<double>{0.8, 0.6, 0.2}, 1.0);

    // add to scene
    material_test_scene.add(
        std::make_shared<primitives::Sphere>(math::vec3<double>{0.0, -100.5, -1.0}, 100.0, material_ground));
    material_test_scene.add(
        std::make_shared<primitives::Sphere>(math::vec3<double>{0.0, 0.0, -1.2}, 0.5, material_center));
    material_test_scene.add(
        std::make_shared<primitives::Sphere>(math::vec3<double>{-1.0, 0.0, -1.0}, 0.5, material_left));
    material_test_scene.add(
        std::make_shared<primitives::Sphere>(math::vec3<double>{-1.0, 0.0, -1.0}, 0.4, material_bubble));
    material_test_scene.add(
        std::make_shared<primitives::Sphere>(math::vec3<double>{1.0, 0.0, -1.0}, 0.5, material_right));

    auto camera_test_material_left = std::make_shared<Lambertian>(math::vec3<double>{0, 0, 1});
    auto camera_test_material_right = std::make_shared<Lambertian>(math::vec3<double>{1, 0, 0});

    double camera_test_len = std::cos(math::MY_PI / 4);
    camera_test_scene.add(std::make_shared<primitives::Sphere>(math::vec3<double>{-camera_test_len, 0, -1},
                                                               camera_test_len, camera_test_material_left));
    camera_test_scene.add(std::make_shared<primitives::Sphere>(math::vec3<double>{camera_test_len, 0, -1},
                                                               camera_test_len, camera_test_material_right));
    // Set the scene
    m_scene = std::move(material_test_scene);
    functional::Logger::get_instance()->debug("Scene initialized!");
}
void Application::initialize_instance()
{
    // init logger
    functional::Logger::create_instance();
    functional::Logger::get_instance()->debug("Logger initialized!");

    // inti image generator
    functional::ImageGenerator::create_instance();
    functional::Logger::get_instance()->debug("ImageGenerator initialized!");
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
