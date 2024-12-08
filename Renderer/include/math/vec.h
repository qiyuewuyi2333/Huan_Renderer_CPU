#pragma once

#include <cmath>
#include <type_traits>
#include "functional/utils/random.h"

namespace huan_renderer_cpu
{
namespace math
{

template <typename T = double>
class vec2
{
  public:
    T x, y;

    // Constructors
    constexpr vec2() : x(T()), y(T())
    {
    }
    constexpr vec2(T _x, T _y) : x(_x), y(_y)
    {
    }

    // Arithmetic operators
    constexpr vec2 operator+(const vec2& other) const
    {
        return vec2{x + other.x, y + other.y};
    }

    constexpr vec2 operator-(const vec2& other) const
    {
        return vec2{x - other.x, y - other.y};
    }

    constexpr vec2 operator-() const
    {
        return vec2{-x, -y};
    }

    constexpr vec2& operator+=(const vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr vec2& operator-=(const vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Scalar multiplication and division
    constexpr vec2 operator*(T scalar) const
    {
        return vec2{x * scalar, y * scalar};
    }

    constexpr friend vec2 operator*(T scalar, const vec2& v)
    {
        return v * scalar;
    }

    constexpr vec2 operator/(T scalar) const
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be a numeric type");
        return vec2{x / scalar, y / scalar};
    }

    // Component-wise multiplication and division
    constexpr vec2 operator*(const vec2& other) const
    {
        return vec2{x * other.x, y * other.y};
    }

    constexpr vec2 operator/(const vec2& other) const
    {
        static_assert(std::is_arithmetic<T>::value, "Components must be numeric types");
        return vec2{x / other.x, y / other.y};
    }

    // Dot product
    constexpr T dot(const vec2& other) const
    {
        return x * other.x + y * other.y;
    }

    // Normalization
    constexpr vec2 normalized() const
    {
        T len = std::sqrt(dot(*this));
        return *this / len;
    }

    void normalize()
    {
        *this = normalized();
    }
};

template <typename T = double>
class vec3
{
  public:
    T x, y, z;

    // Constructors
    constexpr vec3() : x(T()), y(T()), z(T())
    {
    }
    constexpr vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
    {
    }

    // Arithmetic operators
    constexpr vec3 operator+(const vec3& other) const
    {
        return vec3{x + other.x, y + other.y, z + other.z};
    }

    constexpr vec3 operator-(const vec3& other) const
    {
        return vec3{x - other.x, y - other.y, z - other.z};
    }

    constexpr vec3 operator-() const
    {
        return vec3{-x, -y, -z};
    }

    constexpr vec3& operator+=(const vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    constexpr vec3& operator-=(const vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // Scalar multiplication and division
    constexpr vec3 operator*(T scalar) const
    {
        return vec3{x * scalar, y * scalar, z * scalar};
    }

    constexpr friend vec3 operator*(T scalar, const vec3& v)
    {
        return v * scalar;
    }

    constexpr vec3 operator/(T scalar) const
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be a numeric type");
        return vec3{x / scalar, y / scalar, z / scalar};
    }
    constexpr vec3& operator/=(T scalar)
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be a numeric type");
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // Component-wise multiplication and division
    constexpr vec3 operator*(const vec3& other) const
    {
        return vec3{x * other.x, y * other.y, z * other.z};
    }
    constexpr vec3& operator*=(const vec3& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }
    constexpr vec3& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    constexpr vec3 operator/(const vec3& other) const
    {
        static_assert(std::is_arithmetic<T>::value, "Components must be numeric types");
        return vec3{x / other.x, y / other.y, z / other.z};
    }

    // Dot product
    constexpr T dot(const vec3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    constexpr friend vec3 cross(const vec3& lhs, const vec3& rhs)
    {
        return vec3{lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
    }

    // Normalization
    constexpr vec3 normalized() const
    {
        T len = std::sqrt(dot(*this));
        return *this / len;
    }

    void normalize()
    {
        *this = normalized();
    }
    inline bool is_near_zero() const
    {
        return (std::fabs(x) < 1e-8) && (std::fabs(y) < 1e-8) && (std::fabs(z) < 1e-8);
    }
    inline bool is_near_zero()
    {
        return (std::fabs(x) < 1e-8) && (std::fabs(y) < 1e-8) && (std::fabs(z) < 1e-8);
    }

    inline static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};
inline vec3<double> random_unit_vector()
{
    while (true)
    {
        auto p = vec3<double>::random(-1, 1);
        auto lensq = p.dot(p);
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}
inline vec3<double> random_vec_on_hemisphere(const vec3<double>& normal)
{
    vec3<double> on_unit_sphere = random_unit_vector();
    if (on_unit_sphere.dot(normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}
inline vec3<double> reflect(const vec3<double>& v, const vec3<double>& n)
{
    return v - 2 * v.dot(n) * n;
}

template <typename T = double>
class vec4
{
  public:
    T x, y, z, w;

    // Constructors
    constexpr vec4() : x(T()), y(T()), z(T()), w(T())
    {
    }
    constexpr vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w)
    {
    }

    // Arithmetic operators
    constexpr vec4 operator+(const vec4& other) const
    {
        return vec4{x + other.x, y + other.y, z + other.z, w + other.w};
    }

    constexpr vec4 operator-(const vec4& other) const
    {
        return vec4{x - other.x, y - other.y, z - other.z, w - other.w};
    }

    constexpr vec4 operator-() const
    {
        return vec4{-x, -y, -z, -w};
    }

    constexpr vec4& operator+=(const vec4& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    constexpr vec4& operator-=(const vec4& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    // Scalar multiplication and division
    constexpr vec4 operator*(T scalar) const
    {
        return vec4{x * scalar, y * scalar, z * scalar, w * scalar};
    }

    constexpr friend vec4 operator*(T scalar, const vec4& v)
    {
        return v * scalar;
    }

    constexpr vec4 operator/(T scalar) const
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be a numeric type");
        return vec4{x / scalar, y / scalar, z / scalar, w / scalar};
    }

    // Component-wise multiplication and division
    constexpr vec4 operator*(const vec4& other) const
    {
        return vec4{x * other.x, y * other.y, z * other.z, w * other.w};
    }

    constexpr vec4 operator/(const vec4& other) const
    {
        static_assert(std::is_arithmetic<T>::value, "Components must be numeric types");
        return vec4{x / other.x, y / other.y, z / other.z, w / other.w};
    }

    // Dot product
    constexpr T dot(const vec4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // Normalization
    constexpr vec4 normalized() const
    {
        T len = std::sqrt(dot(*this));
        return *this / len;
    }

    void normalize()
    {
        *this = normalized();
    }
};

} // namespace math
} // namespace huan_renderer_cpu
