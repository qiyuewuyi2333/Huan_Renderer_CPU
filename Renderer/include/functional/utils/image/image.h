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
    Image(uint32_t width, uint32_t height, double aspect_ratio);
    Image(const Image& image);
    Image(Image&& image) = delete;
    Image& operator=(const Image& image);
    Image& operator=(Image&& image) = delete;
    ~Image();

    void set_pixel(uint32_t x, uint32_t y, double r, double g, double b);
    void set_pixel(uint32_t x, uint32_t y, const Color& color);
    Color get_pixel(uint32_t x, uint32_t y) const;
    uint32_t get_width() const;
    uint32_t get_height() const;

  private:
    uint32_t m_width, m_height;
    std::vector<Color> m_pixels;
    double m_aspect_ratio;
};
} // namespace functional
} // namespace huan_renderer_cpu
