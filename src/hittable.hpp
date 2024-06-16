#ifndef RT_HITTABLEH
#define RT_HITTABLEH

#include <core.hpp>

class Material;
struct HitResponse {
    point3 point;
    Vec3 normal;
    float step;
    bool outsideFace;

    std::shared_ptr<Material> material;

    void setFaceNormal(const Ray& ray, const Vec3& outsideNormal)
    {
        outsideFace = dot(ray.dir(), outsideNormal) < 0;
        normal = outsideFace ? outsideNormal : (-1 * outsideNormal);
    }
};

class Hittable {

public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, Interval rayStep, HitResponse& responses) const = 0;
};

#endif
