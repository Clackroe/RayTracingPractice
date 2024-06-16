#include <core.hpp>

Vec3 Vec3::random()
{
    return Vec3(randomFloat(), randomFloat(), randomFloat());
}

Vec3 Vec3::random(float min, float max)
{
    return Vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}
