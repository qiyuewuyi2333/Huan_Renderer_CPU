#include "functional/utils/image/image.h"
namespace huan_renderer_cpu
{
namespace functional
{
Image::Image(size_t width, size_t height) : width(width), height(height), pixels(width * height)
{
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
void Image::set_pixel(size_t x, size_t y, float r, float g, float b)
{
    int index = x + y * width;
    pixels[index] = Color(r, g, b);
}
void Image::set_pixel(size_t x, size_t y, const Color& color)
{
    int index = x + y * width;
    pixels[index] = color;
}
Color Image::get_pixel(size_t x, size_t y) const
{
    int index = x + y * width;
    return pixels[index];
}
size_t Image::get_width() const
{
    return width;
}
size_t Image::get_height() const
{
    return height;
}
} // namespace functional
} // namespace huan_renderer_cpu