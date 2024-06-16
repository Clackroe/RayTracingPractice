#include <ray.hpp>

Ray::Ray() {};
Ray::Ray(const Vec3& origin, const Vec3& dir)
    : m_Origin(origin)
    , m_Direction(dir) {};

const point3& Ray::origin() const { return m_Origin; };
const Vec3& Ray::dir() const { return m_Direction; };

point3 Ray::at(float stepT) const
{
    return m_Origin + (stepT * m_Direction);
};
