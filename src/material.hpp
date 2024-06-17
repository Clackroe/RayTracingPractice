#ifndef RT_MATREIALH
#define RT_MATREIALH
#include "hittable.hpp"
#include "vec3.hpp"
#include <core.hpp>

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
    Metal(const color& albedo, float fuzziness)
        : m_Albedo(albedo)
        , m_Fuzz(fuzziness < 1 ? fuzziness : 1)
    {
    }

    bool scatter(const Ray& ray, const HitResponse& response, color& attuention, Ray& scattered) const override
    {
        Vec3 reflected = reflect(ray.dir(), response.normal);
        reflected = unitVector(reflected) + (m_Fuzz * randomUnitVector());
        scattered = Ray(response.point, reflected);
        attuention = m_Albedo;
        return (dot(scattered.dir(), response.normal) > 0);
    }

private:
    color m_Albedo;
    float m_Fuzz;
};

static float reflectance(float cosine, float refIndex)
{
    // Using Schlick's Approximation for reflectance as stated in the book
    float r0 = (1 - refIndex) / (1 + refIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

class Dielectric : public Material {
public:
    Dielectric(float refractionIndex)
        : m_RefractionIndex(refractionIndex) {};

    bool scatter(const Ray& ray, const HitResponse& response, color& attuention, Ray& scattered) const override
    {

        attuention = color(1, 1, 1);
        float refIndex = response.outsideFace ? (1.0f / m_RefractionIndex) : m_RefractionIndex;

        Vec3 uDir = unitVector(ray.dir());

        float cosTheta = std::fmin(dot(-1 * uDir, response.normal), 1.0f);
        float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

        bool cannotRefract = refIndex * sinTheta > 1.0f;

        Vec3 direction;
        if (cannotRefract || reflectance(cosTheta, refIndex) > randomFloat()) {
            direction = reflect(uDir, response.normal);
        } else {
            direction = refract(uDir, response.normal, refIndex);
        }

        scattered = Ray(response.point, direction);
        return true;
    }

private:
    float m_RefractionIndex;
};
#endif
