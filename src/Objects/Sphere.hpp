#ifndef RT_SPHEREH
#define RT_SPHEREH

#include <hittable.hpp>

class Sphere : public Hittable {
public:
    Sphere(const point3& center, float rad)
    {
        m_Center = center;
        m_Radius = rad;
    };

    bool hit(const Ray& ray, float stepMin, float stepMax, HitResponse& response) const override
    {
        vec3 oc = m_Center - ray.origin();
        float a = ray.dir().magnitude_squared();
        float h = dot(ray.dir(), oc);
        float c = oc.magnitude_squared() - m_Radius * m_Radius;
        float disc = h * h - a * c;

        if (disc < 0) {
            return false;
        }

        float rootDisc = std::sqrt(disc);

        // Finding which intersection is the closest, based on the quadratic formula
        float root = (h - rootDisc) / a;
        if (root <= stepMin || stepMax <= root) {
            root = (h + rootDisc) / a;
            if (root <= stepMin || stepMax <= root) {
                return false;
            }
        }

        response.step = root;
        response.point = ray.at(response.step);
        vec3 outNorm = (response.point - m_Center) / m_Radius;
        response.setFaceNormal(ray, outNorm);

        return true;
    }

private:
    point3 m_Center;
    float m_Radius;
};
#endif
