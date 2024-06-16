#include <core.hpp>

#include <Objects/Sphere.hpp>
#include <camera.hpp>
#include <hittableList.hpp>

#include <material.hpp>
#include <memory>

int main()
{
    std::shared_ptr<Material> materialGround = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    std::shared_ptr<Material> materialCenter = std::make_shared<Lambertian>(color(0.8, 0.8, 0.8));
    std::shared_ptr<Material> materialLeft = std::make_shared<Metal>(color(0.9, 0.2, 0.2));
    std::shared_ptr<Material> materialRight = std::make_shared<Metal>(color(0.2, 0.2, 0.8));

    int imageWidth = 2560;
    int maxDepth = 50;
    int samplesPerPixel = 10;

    Camera camera(point3(0, 0, 0), imageWidth, (16.0f / 9.0f), 1.0f, samplesPerPixel, maxDepth);

    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(std::make_shared<Sphere>(point3(0.0, 0.0, -1.2), 0.5, materialCenter));
    world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, materialRight));

    camera.render(world);
}
