#include "functional/utils/image/image.h"
namespace huan_renderer_cpu
{
namespace functional
{
Image::Image(uint32_t width, uint32_t height, double aspect_ratio)
    : m_width(width), m_height(height), m_aspect_ratio(aspect_ratio)
{
    m_pixels.resize(width * height);
}

Image::Image(const Image& image)
{
    m_width = image.m_width;
    m_height = image.m_height;
    m_pixels = image.m_pixels;
}
Image& Image::operator=(const Image& image)
{
    m_width = image.m_width;
    m_height = image.m_height;
    m_pixels = image.m_pixels;
    return *this;
}
Image::~Image()
{
    m_pixels.clear();
}
void Image::set_pixel(uint32_t x, uint32_t y, double r, double g, double b)
{
    int index = x + y * m_width;
    m_pixels[index] = Color(r, g, b);
}
void Image::set_pixel(uint32_t x, uint32_t y, const Color& color)
{
    int index = x + y * m_width;
    m_pixels[index] = color;
}
Color Image::get_pixel(uint32_t x, uint32_t y) const
{
    int index = x + y * m_width;
    return m_pixels[index];
}
uint32_t Image::get_width() const
{
    return m_width;
}
uint32_t Image::get_height() const
{
    return m_height;
}
} // namespace functional
} // namespace huan_renderer_cpu
