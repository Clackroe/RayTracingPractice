#include "vec3.hpp"
#include <camera.hpp>
#include <hittable.hpp>
#include <material.hpp>

Camera::Camera(point3 center, float width, float aspectRatio, float focalLength, int samplesPerPixel, int maxDepth)
    : m_SamplesPerPixel(samplesPerPixel)
    , m_SampleScale(1.0f / samplesPerPixel)
    , m_MaxDepth(maxDepth)
    , m_Center(center)
{
    // Setup image
    m_Image.Width = width;
    m_Image.aspectRatio = aspectRatio;
    int iH = int(m_Image.Width / m_Image.aspectRatio);
    m_Image.Height = iH < 1 ? 1 : iH;

    m_FocalLength = focalLength;
    m_VP.Width = m_VP.Height * m_Image.aspectRatio;

    m_VP.u = Vec3(m_VP.Width, 0, 0);
    m_VP.v = Vec3(0, -m_VP.Height, 0);

    m_VP.deltaU = m_VP.u / m_Image.Width;
    m_VP.deltaV = m_VP.v / m_Image.Height;

    m_TopLeft = m_Center - Vec3(0, 0, m_FocalLength) - m_VP.u / 2 - m_VP.v / 2;
    m_PixelTopLeft = m_TopLeft + 0.5f * (m_VP.deltaU + m_VP.deltaV);
};

color Camera::rayColor(const Ray& ray, int depth, const Hittable& world) const
{
    if (depth <= 0) {
        return color(0, 0, 0);
    }
    HitResponse response;

    if (world.hit(ray, Interval(0.001, +infinity), response)) {

        Ray scattered;
        color attenuation;
        if (response.material->scatter(ray, response, attenuation, scattered)) {

            return attenuation * rayColor(scattered, depth - 1, world);
        }
        return color(0, 0, 0);
    }

    Vec3 uDirection = unitVector(ray.dir());
    float s = 0.5 * (uDirection.getY() + 1.0f);
    return (1.0f - s) * color(1.0f, 1.0f, 1.0f) + s * color(0.5f, 0.7f, 1.0f);
}

Ray Camera::getRay(int x, int y) const
{
    Vec3 offset = sampleSquare();
    Vec3 sample = m_PixelTopLeft + ((x + offset.getX()) * m_VP.deltaU)
        + ((y + offset.getY()) * m_VP.deltaV);

    Vec3 dir = sample - m_Center;
    return Ray(m_Center, dir);
};

Vec3 Camera::sampleSquare() const
{
    return Vec3(randomFloat() - 0.5, randomFloat() - 0.5, 0);
};

void Camera::render(const Hittable& world) const
{
    std::cout << "P3\n"
              << m_Image.Width << " " << m_Image.Height << "\n255\n";

    for (int y = 0; y < m_Image.Height; y++) {
        std::clog << "\rScanlines remaining: " << (m_Image.Height - y) << ' ' << std::flush;
        for (int x = 0; x < m_Image.Width; x++) {

            color pixelColor(0, 0, 0);
            for (int i = 0; i < m_SamplesPerPixel; i++) {
                Ray r = getRay(x, y);
                pixelColor += rayColor(r, m_MaxDepth, world);
            }
            pixelColor *= m_SampleScale;

            Color::writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
};
