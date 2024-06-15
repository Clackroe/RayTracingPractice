#ifndef RT_VEC3H
#define RT_VEC3H
#include <cmath>
#include <iostream>
class vec3 {

public:
    vec3() { }

    vec3(float a, float b, float c)
    {
        data[0] = a;
        data[1] = b;
        data[2] = c;
    }

    float data[3];

    float getX() const { return data[0]; }
    float getY() const { return data[1]; }
    float getZ() const { return data[2]; }

    vec3& operator*=(float scalar)
    {
        data[0] *= scalar;
        data[1] *= scalar;
        data[2] *= scalar;
        return *this;
    }

    vec3& operator+=(const vec3& other)
    {
        data[0] += other.data[0];
        data[1] += other.data[1];
        data[2] += other.data[2];
        return *this;
    }

    vec3& operator/=(float div)
    {
        return *this *= 1 / div;
    }

    float magnitude_squared() const
    {
        return (data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]);
    }
    float magnitude() const
    {
        return std::sqrt(magnitude_squared());
    }
};

// For more readable code
using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.data[0] << ' ' << v.data[1] << ' ' << v.data[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3({ u.data[0] + v.data[0], u.data[1] + v.data[1], u.data[2] + v.data[2] });
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3({ u.data[0] - v.data[0], u.data[1] - v.data[1], u.data[2] - v.data[2] });
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3({ u.data[0] * v.data[0], u.data[1] * v.data[1], u.data[2] * v.data[2] });
}

inline vec3 operator*(float t, const vec3& v)
{
    return vec3({ t * v.data[0], t * v.data[1], t * v.data[2] });
}

inline vec3 operator*(const vec3& v, float t)
{
    return t * v;
}

inline vec3 operator/(const vec3& v, float t)
{
    return (1 / t) * v;
}

inline float dot(const vec3& u, const vec3& v)
{
    return u.data[0] * v.data[0]
        + u.data[1] * v.data[1]
        + u.data[2] * v.data[2];
}

inline vec3 cross(const vec3& u, const vec3& v)
{
    return vec3({ u.data[1] * v.data[2] - u.data[2] * v.data[1],
        u.data[2] * v.data[0] - u.data[0] * v.data[2],
        u.data[0] * v.data[1] - u.data[1] * v.data[0] });
}

inline vec3 unit_vector(const vec3& v)
{
    return v / v.magnitude();
}

#endif
