#ifndef RT_MATREIALH
#define RT_MATREIALH
#include "hittable.hpp"
#include "vec3.hpp"
#include <core.hpp>
#include <functional>

class Material {

public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray, const HitResponse& response, color& attuention, Ray& scattered) const { return false; }
};

class Lambertian : public Material {

public:
    Lambertian(const color& albedo)
        : m_Albedo(albedo)
    {
    }

    bool scatter(const Ray& ray, const HitResponse& response, color& attuention, Ray& scattered) const override
    {
        Vec3 scatterDir = response.normal + randomUnitVector();

        if (scatterDir.nearZero()) {
            scatterDir = response.normal;
        }

        scattered = Ray(response.point, scatterDir);
        attuention = m_Albedo;
        return true;
    }

private:
    color m_Albedo;
};

class Metal : public Material {
public:
    Metal(const color& albedo)
        : m_Albedo(albedo)
    {
    }

    bool scatter(const Ray& ray, const HitResponse& response, color& attuention, Ray& scattered) const override
    {
        Vec3 reflected = reflect(ray.dir(), response.normal);
        scattered = Ray(response.point, reflected);
        attuention = m_Albedo;
        return true;
    }

private:
    color m_Albedo;
};
#endif
