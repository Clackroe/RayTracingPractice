#ifndef RT_RAYH
#define RT_RAYH
#include <vec3.hpp>

class Ray {
public:
    Ray();
    Ray(const vec3& origin, const vec3& dir);

    const point3& origin() const;
    const vec3& dir() const;

    point3 at(float stepT) const;

private:
    point3 m_Origin;
    vec3 m_Direction;
};

#endif
