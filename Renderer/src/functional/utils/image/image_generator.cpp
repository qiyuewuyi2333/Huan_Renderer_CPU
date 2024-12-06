#include "functional/utils/image/image_generator.h"
#include "core/core.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace huan_renderer_cpu
{

namespace functional
{
ImageGenerator* ImageGenerator::instance = nullptr;

void ImageGenerator::create_instance()
{
    if (instance == nullptr)
    {
        instance = new ImageGenerator();
    }
}
void ImageGenerator::destroy_instance()
{
    if (instance != nullptr)
    {
        delete instance;
    }
}
ImageGenerator* ImageGenerator::get_instance()
{
    if (instance == nullptr)
    {
        RENDERER_ASSERT(true, "You should create the ImageGenerator instance first!");
        return nullptr;
    }
    return instance;
}

void ImageGenerator::save(std::string_view path, const std::shared_ptr<huan_renderer_cpu::functional::Image>& image)
{

    // 输出文件路径
    std::cout << "Saving image to: " << path << std::endl;

    std::ofstream file(path.data(), std::ios_base::out | std::ios::binary);
    RENDERER_ASSERT(file.is_open(), "Failed to open file:" + path);

    const int width = image->get_width();
    const int height = image->get_height();
    file << "P6\n" << width << " " << height << "\n255\n";

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            const auto& pixel = image->get_pixel(x, y).norm_color_to_255();

            file << static_cast<char>(pixel.x) << static_cast<char>(pixel.y) << static_cast<char>(pixel.z);
        }
    }
}
} // namespace functional
} // namespace huan_renderer_cpu
