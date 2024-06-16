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
    Camera(point3 center, float width, float aspectRatio, float focalLength, int samplesPerPixel, int maxDepth);

    void render(const Hittable& world) const;

private:
    color rayColor(const Ray& ray, int depth, const Hittable& world) const;

    Ray getRay(int x, int y) const;
    Vec3 sampleSquare() const;

    point3 m_Center;
    float m_FocalLength = 1.0f;

    int m_SamplesPerPixel;
    float m_SampleScale;

    int m_MaxDepth;

    Image m_Image;
    ViewPortData m_VP;

    Vec3 m_TopLeft, m_PixelTopLeft;
};
#endif
