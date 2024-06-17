#include <camera.hpp>
#include <core.hpp>
#include <hittable.hpp>
#include <material.hpp>

#include <sstream>

#include <mutex>
#include <thread>

Camera::Camera(point3 center, float width, float aspectRatio, int samplesPerPixel, int maxDepth, float fov, float dofAng, float dofDist)
    : m_SamplesPerPixel(samplesPerPixel)
    , m_SampleScale(1.0f / samplesPerPixel)
    , m_MaxDepth(maxDepth)
    , lookFrom(center)
    , FOV(fov)
    , dofAngle(dofAng)
    , dofDistance(dofDist)
{

    m_Center = lookFrom;

    // Setup image
    m_Image.Width = width;
    m_Image.aspectRatio = aspectRatio;
    int iH = int(m_Image.Width / m_Image.aspectRatio);
    m_Image.Height = iH < 1 ? 1 : iH;

    float theta = degreesToRadians(FOV);
    float h = std::tan(theta / 2);

    // m_FocalLength = (lookFrom - lookAt).magnitude();

    m_VP.Height = 2 * h * dofDistance;
    m_VP.Width = m_VP.Height * m_Image.aspectRatio;

    w = unitVector(lookFrom - lookAt);
    u = unitVector(cross(viewUp, w));
    v = cross(w, u);

    m_VP.u = m_VP.Width * u;
    m_VP.v = m_VP.Height * (-1 * v);

    m_VP.deltaU = m_VP.u / m_Image.Width;
    m_VP.deltaV = m_VP.v / m_Image.Height;

    m_TopLeft = m_Center - (dofDistance * w) - m_VP.u / 2 - m_VP.v / 2;
    m_PixelTopLeft = m_TopLeft + 0.5f * (m_VP.deltaU + m_VP.deltaV);

    float dofRad = dofDistance * std::tan(degreesToRadians(dofAngle / 2));
    m_DofDiscU = u * dofRad;
    m_DofDiscV = v * dofRad;
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

point3 Camera::dofDiscSample() const
{
    Vec3 point = randomInUnitDisc();
    return m_Center + (point.getX() * m_DofDiscU) + (point.getY() * m_DofDiscV);
}

Ray Camera::getRay(int x, int y) const
{
    Vec3 offset = sampleSquare();
    Vec3 sample = m_PixelTopLeft + ((x + offset.getX()) * m_VP.deltaU)
        + ((y + offset.getY()) * m_VP.deltaV);

    Vec3 org = (dofAngle <= 0) ? m_Center : dofDiscSample();
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

    const int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<std::ostringstream> buffers(numThreads);
    std::mutex clogMutex;
    std::atomic<int> scanlinesRemaining(m_Image.Height);

    auto renderSection = [&](int startY, int endY, int threadIndex) {
        std::ostringstream& buffer = buffers[threadIndex];
        for (int y = startY; y < endY; y++) {
            {
                int remaining = --scanlinesRemaining;
                std::lock_guard<std::mutex> lock(clogMutex);
                std::clog << "\rScanlines remaining: " << remaining << ' ' << std::flush;
            }
            for (int x = 0; x < m_Image.Width; x++) {
                color pixelColor(0, 0, 0);
                for (int i = 0; i < m_SamplesPerPixel; i++) {
                    Ray r = getRay(x, y);
                    pixelColor += rayColor(r, m_MaxDepth, world);
                }
                pixelColor *= m_SampleScale;

                Color::writeColor(buffer, pixelColor);
            }
        }
    };

    int rowsPerThread = m_Image.Height / numThreads;
    for (int i = 0; i < numThreads; i++) {
        int startY = i * rowsPerThread;
        int endY = (i == numThreads - 1) ? m_Image.Height : startY + rowsPerThread;
        threads.emplace_back(renderSection, startY, endY, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    // Output the contents of each buffer sequentially
    for (const auto& buffer : buffers) {
        std::cout << buffer.str();
    }

    std::clog << "\rDone.                 \n";
}
