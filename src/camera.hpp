#ifndef RT_CAMERAH
#define RT_CAMERAH
#include "hittable.hpp"
#include <core.hpp>

struct Image {
    float aspectRatio = 16.0f / 9.0f;
    int Width = 400;
    int Height;
};

struct ViewPortData {
    float Width;
    float Height = 2.0f;
    Vec3 u, v;
    Vec3 deltaU, deltaV;
};

class Camera {
public:
    Camera(point3 center, float width, float aspectRatio, int samplesPerPixel, int maxDepth, float fov, float dofAng, float dofDist);

    void render(const Hittable& world) const;

    float FOV = 90;
    point3 lookFrom = point3(-2, -2, -2);
    point3 lookAt = point3(0, 0, 0);
    Vec3 viewUp = Vec3(0, 1, 0);

    Vec3 u, v, w;

    float dofAngle, dofDistance;

private:
    color rayColor(const Ray& ray, int depth, const Hittable& world) const;

    Ray getRay(int x, int y) const;
    Vec3 sampleSquare() const;
    point3 dofDiscSample() const;

    point3 m_Center;
    float m_FocalLength = 1.0f;

    int m_SamplesPerPixel;
    float m_SampleScale;

    int m_MaxDepth;

    Image m_Image;
    ViewPortData m_VP;

    Vec3 m_DofDiscU, m_DofDiscV;

    Vec3 m_TopLeft, m_PixelTopLeft;
};
#endif
