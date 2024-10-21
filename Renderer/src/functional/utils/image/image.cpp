#include "functional/utils/image/image.h"
namespace huan_renderer_cpu
{
namespace functional
{
Image::Image(uint32_t width, uint32_t height) : width(width), height(height)
{
    pixels.resize(width * height);
}

Image::Image(const Image& image)
{
    width = image.width;
    height = image.height;
    pixels = image.pixels;
}
Image& Image::operator=(const Image& image)
{
    width = image.width;
    height = image.height;
    pixels = image.pixels;
    return *this;
}
Image::~Image()
{
    pixels.clear();
}
void Image::set_pixel(uint32_t x, uint32_t y, float r, float g, float b)
{
    int index = x + y * width;
    pixels[index] = Color(r, g, b);
}
void Image::set_pixel(uint32_t x, uint32_t y, const Color& color)
{
    int index = x + y * width;
    pixels[index] = color;
}
Color Image::get_pixel(uint32_t x, uint32_t y) const
{
    int index = x + y * width;
    return pixels[index];
}
uint32_t Image::get_width() const
{
    return width;
}
uint32_t Image::get_height() const
{
    return height;
}
} // namespace functional
} // namespace huan_renderer_cpu