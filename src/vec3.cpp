#include <core.hpp>

Vec3 Vec3::random()
{
    return Vec3(randomFloat(), randomFloat(), randomFloat());
}

Vec3 Vec3::random(float min, float max)
{
    return Vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}

extern Vec3 randomInUnitDisc()
{
    while (true) {
        Vec3 point = Vec3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
        if (point.magnitude() < 1) {
            return point;
        }
    }
}
