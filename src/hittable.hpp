#ifndef RT_HITTABLEH
#define RT_HITTABLEH

#include <core.hpp>

struct HitResponse {
    point3 point;
    vec3 normal;
    float step;
    bool outsideFace;

    void setFaceNormal(const Ray& ray, const vec3& outsideNormal)
    {
        outsideFace = dot(ray.dir(), outsideNormal) < 0;
        normal = outsideFace ? outsideNormal : (-1 * outsideNormal);
    }
};

class Hittable {

public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, float stepMin, float stepMax, HitResponse& responses) const = 0;
};

#endif
