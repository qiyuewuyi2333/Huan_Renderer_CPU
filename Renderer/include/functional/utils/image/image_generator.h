#pragma once
#include "functional/utils/image/image.h"
#include <memory>
#include <string_view>
namespace huan_renderer_cpu
{

namespace functional
{
class ImageGenerator
{
  public:
    ImageGenerator() : image_comment("# HUAN CREATED") {}
    static void create_instance();
    static void destroy_instance();
    static ImageGenerator* get_instance();

    void save(std::string_view path, const std::shared_ptr<huan_renderer_cpu::functional::Image>& image);

  private:
    static ImageGenerator* instance;
    static constexpr int MAX_THREAD_NUM = 8;
    static constexpr int MAX_IMAGE_SIZE = 4096;
    static constexpr int MAX_IMAGE_PIXEL_NUM = MAX_IMAGE_SIZE * MAX_IMAGE_SIZE;
    std::string_view image_comment;
};

} // namespace functional

} // namespace huan_renderer_cpu