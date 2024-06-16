#ifndef RT_VEC3H
#define RT_VEC3H
#include <cmath>
#include <iostream>
class Vec3 {

public:
    Vec3() { }

    Vec3(float a, float b, float c)
    {
        data[0] = a;
        data[1] = b;
        data[2] = c;
    }

    float data[3];

    float getX() const { return data[0]; }
    float getY() const { return data[1]; }
    float getZ() const { return data[2]; }

    Vec3& operator*=(float scalar)
    {
        data[0] *= scalar;
        data[1] *= scalar;
        data[2] *= scalar;
        return *this;
    }

    Vec3& operator+=(const Vec3& other)
    {
        data[0] += other.data[0];
        data[1] += other.data[1];
        data[2] += other.data[2];
        return *this;
    }

    Vec3& operator/=(float div)
    {
        return *this *= 1 / div;
    }

    float magnitudeSquared() const
    {
        return (data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]);
    }
    float magnitude() const
    {
        return std::sqrt(magnitudeSquared());
    }

    bool nearZero() const
    {
        float s = 1e-8;
        return (std::fabs(data[0]) < s) && (std::fabs(data[1]) < s) && (std::fabs(data[2]) < s);
    }

    static Vec3 random();

    static Vec3 random(float min, float max);
};

// For more readable code
using point3 = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.data[0] << ' ' << v.data[1] << ' ' << v.data[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3({ u.data[0] + v.data[0], u.data[1] + v.data[1], u.data[2] + v.data[2] });
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3({ u.data[0] - v.data[0], u.data[1] - v.data[1], u.data[2] - v.data[2] });
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3({ u.data[0] * v.data[0], u.data[1] * v.data[1], u.data[2] * v.data[2] });
}

inline Vec3 operator*(float t, const Vec3& v)
{
    return Vec3({ t * v.data[0], t * v.data[1], t * v.data[2] });
}

inline Vec3 operator*(const Vec3& v, float t)
{
    return t * v;
}

inline Vec3 operator/(const Vec3& v, float t)
{
    return (1 / t) * v;
}

inline float dot(const Vec3& u, const Vec3& v)
{
    return u.data[0] * v.data[0]
        + u.data[1] * v.data[1]
        + u.data[2] * v.data[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3({ u.data[1] * v.data[2] - u.data[2] * v.data[1],
        u.data[2] * v.data[0] - u.data[0] * v.data[2],
        u.data[0] * v.data[1] - u.data[1] * v.data[0] });
}

inline Vec3 unitVector(const Vec3& v)
{
    return v / v.magnitude();
}

inline Vec3 randomInUnitSphere()
{
    while (true) {
        Vec3 v = Vec3::random(-1, 1);
        if (v.magnitude() < 1) {
            return v;
        }
    }
}

inline Vec3 randomUnitVector()
{
    return unitVector(randomInUnitSphere());
}

inline Vec3 randomInHemisphere(const Vec3& normal)
{
    Vec3 v = randomUnitVector();
    if (dot(v, normal) > 0.0f) {
        return v;
    } else {
        return -1 * v;
    }
}

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
    float a = dot(v, n);
    Vec3 b = a * n;

    return v - (2 * b);
}

#endif
