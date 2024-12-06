#pragma once

#include "functional/thread/thread_pool.h"
#include "functional/thread/task.h"
#include "functional/utils/image/image.h"
#include "core/camera.h"
#include "core/hittable_lists.h"
#include "functional/utils/image/image_generator.h"
namespace huan_renderer_cpu
{
struct ApplicationSetting
{
    bool enable_vsync = true; // Enable or disable vertical sync
};
struct RenderSetting
{
    bool enable_anti_aliasing = true; // Enable or disable anti-aliasing
    int sample_count = 10;            // Number of samples for anti-aliasing
    // sample_scale

    // Image
    std::string image_format = "ppm"; // Format of the rendered image
    double aspect_ratio = 16.0 / 9.0;
    uint32_t image_height = 1080;
    uint32_t image_width = image_height * aspect_ratio;
};
class Application
{
  public:
    Application();
    Application(Application&&) = delete;
    Application(const Application&) = delete;
    Application& operator=(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    ~Application() = default;
    static void create_instance()
    {
        if (instance == nullptr)
        {
            instance = new Application();
        }
    }
    static Application* get_instance()
    {
        if (!instance)
            return nullptr;
        return instance;
    }

  public:
    void render();

  public:
    void initialize();
    void initialize_instance();
    void destory();

    void save_image(const std::string& name);

  private:
    ApplicationSetting m_app_setting;
    RenderSetting m_render_setting;
    std::unique_ptr<functional::ThreadPool> m_thread_pool;
    std::shared_ptr<functional::Image> m_image;
    std::unique_ptr<functional::ImageGenerator> m_image_generator;
    std::unique_ptr<Camera> m_camera;
    huan_renderer_cpu::HittableLists m_scene;

  private:
    inline static Application* instance = nullptr;
};

} // namespace huan_renderer_cpu
