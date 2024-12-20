#include "functional/utils/image/image_generator.h"
#include "core/core.h"
#include "math/vec.h"
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
            auto pixel = image->get_pixel(x, y);
            pixel.r = linear_to_gamma(pixel.r);
            pixel.g = linear_to_gamma(pixel.g);
            pixel.b = linear_to_gamma(pixel.b);
            math::vec3<int> new_pixel = pixel.norm_color_to_255();

            file << static_cast<char>(new_pixel.x) << static_cast<char>(new_pixel.y) << static_cast<char>(new_pixel.z);
        }
    }
}
double ImageGenerator::linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}
} // namespace functional
} // namespace huan_renderer_cpu
