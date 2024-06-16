#ifndef RT_RAYH
#define RT_RAYH
#include <vec3.hpp>

class Ray {
public:
    Ray();
    Ray(const Vec3& origin, const Vec3& dir);

    const point3& origin() const;
    const Vec3& dir() const;

    point3 at(float stepT) const;

private:
    point3 m_Origin;
    Vec3 m_Direction;
};

#endif
