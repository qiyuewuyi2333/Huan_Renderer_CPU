#include "functional/utils/image/image_generator.h"
#include "core/core.h"
#include <filesystem>
#include <fstream>

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
    std::ofstream file(path.data(), std::ios_base::out | std::ios::binary);
    RENDERER_ASSERT(file.is_open(), "Failed to open file:" + path);

    const int width = image->get_width();
    const int height = image->get_height();
    file << "P6\n" << width << " " << height << "\n255\n";

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            const auto& pixel = image->get_pixel(x, y);

            file << static_cast<char>(pixel.r * 255) << static_cast<char>(pixel.g * 255)
                 << static_cast<char>(pixel.b * 255);
        }
    }
}
} // namespace functional
} // namespace huan_renderer_cpu