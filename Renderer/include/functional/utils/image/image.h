#pragma once

#include <vector>
#include "functional/utils/image/color.h"

namespace huan_renderer_cpu
{
namespace functional
{

/**
 * @brief Abstraction of Image. Need to use ImageGenerator to persist.
 * 
 */
class Image
{
  public:
    Image(size_t width, size_t height);
    Image(const Image& image);
    Image(Image&& image) = delete;
    Image& operator=(const Image& image);
    Image& operator=(Image&& image) = delete;
    ~Image();

    void set_pixel(size_t x, size_t y, float r, float g, float b);
    void set_pixel(size_t x, size_t y, const Color& color);
    Color get_pixel(size_t x, size_t y) const;
    size_t get_width() const;
    size_t get_height() const;
  private:
    size_t width, height;
    std::vector<Color>   pixels;
};
} // namespace functional
} // namespace huan_renderer_cpu