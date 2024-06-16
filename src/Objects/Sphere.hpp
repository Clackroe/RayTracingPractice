#ifndef RT_SPHEREH
#define RT_SPHEREH

#include <hittable.hpp>
#include <memory>

class Sphere : public Hittable {
public:
    Sphere(const point3& center, float rad, std::shared_ptr<Material> mat)
    {
        m_Center = center;
        m_Radius = rad;
        m_Material = mat;
    };

    bool hit(const Ray& ray, Interval rayStep, HitResponse& response) const override
    {
        Vec3 oc = m_Center - ray.origin();
        float a = ray.dir().magnitudeSquared();
        float h = dot(ray.dir(), oc);
        float c = oc.magnitudeSquared() - m_Radius * m_Radius;
        float disc = h * h - a * c;

        if (disc < 0) {
            return false;
        }

        float rootDisc = std::sqrt(disc);

        // Finding which intersection is the closest, based on the quadratic formula
        float root = (h - rootDisc) / a;
        if (!rayStep.surrounds(root)) {
            root = (h + rootDisc) / a;
            if (!rayStep.surrounds(root)) {
                return false;
            }
        }

        response.step = root;
        response.point = ray.at(response.step);
        Vec3 outNorm = (response.point - m_Center) / m_Radius;
        response.setFaceNormal(ray, outNorm);
        response.material = m_Material;

        return true;
    }

private:
    point3 m_Center;
    float m_Radius;

    std::shared_ptr<Material> m_Material;
};
#endif
