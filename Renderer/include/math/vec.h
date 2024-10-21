#pragma once

#include <cmath>
namespace huan_renderer_cpu
{
namespace math
{
// TODO FINISH
class vec2;
class vec3;
class vec4;


class vec2
{
  public:
    float x, y;
    inline constexpr vec2 operator+(const vec2& other)
    {
        return vec2{x + other.x, y + other.y};
    }
    inline constexpr vec2 operator-(const vec2& other)
    {
        return vec2{x - other.x, y - other.y};
    }
    inline constexpr friend vec2 operator-(const vec2& rhs, const vec2& lhs)
    {
        return rhs - lhs;
    }
    inline constexpr friend vec2 operator*(float scalar, const vec2& other)
    {
        return vec2{scalar * other.x, scalar * other.y};
    }
    inline constexpr vec2 operator*(const vec2& other)
    {
        return vec2{x * other.x, y * other.y};
    }
    inline constexpr friend vec2 operator*(const vec2& v, const float& val)
    {
        return vec2{v.x * val, v.y * val};
    }
    inline constexpr friend vec2 operator/(const vec2& other, const vec2& v)
    {
        return vec2{other.x / v.x, other.y / v.y};
    }
    inline constexpr friend vec2 operator/(const vec2& other, float scalar)
    {
        return vec2{other.x / scalar, other.y / scalar};
    }
};
class vec3
{
  public:
    float x, y, z;
    inline constexpr vec3 operator+(const vec3& other)
    {
        return vec3{x + other.x, y + other.y, z + other.z};
    }
    inline constexpr friend vec3 operator+(const vec3& rhs, const vec3& lhs)
    {
        return vec3{rhs.x + lhs.x, rhs.y + lhs.y, rhs.z + lhs.z};
    }
    inline constexpr vec3 operator+=(const vec3& other) 
    {
        return vec3{x + other.x, y + other.y, z + other.z};
    }
    inline constexpr friend vec3 operator-(const vec3& rhs, const vec3& lhs)
    {
        return vec3{rhs.x - lhs.x, rhs.y - lhs.y, rhs.z - lhs.z};
    }
    inline constexpr vec3 operator-=(const vec3& other)
    {
        return vec3{x - other.x, y - other.y, z - other.z};
    }
    inline constexpr vec3 operator*(const float rhs) 
    {
        return vec3{x * rhs, y * rhs, z * rhs};
    }
    inline constexpr friend vec3 operator*(const float rhs, const vec3& lhs)
    {
        return vec3{rhs * lhs.x, rhs * lhs.y, rhs * lhs.z};
    }
    inline constexpr vec3 operator/(const float rhs) const
    {
        return vec3{x / rhs, y / rhs, z / rhs};
    }
    inline constexpr float dot(const vec3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
    inline vec3 normalized() const
    {
        return *this / sqrt(dot(*this));
    }
    inline void normalize()
    {
        *this = normalized();
    }
};

inline vec3 cross(const vec3& rhs, const vec3& lhs)
{
    return vec3{rhs.y * lhs.z - rhs.z * lhs.y, rhs.z * lhs.x - rhs.x * lhs.z, rhs.x * lhs.y - rhs.y * lhs.x};
}

class vec4
{
  public:
    float x, y, z, w;
};
} // namespace math
} // namespace huan_renderer_cpu