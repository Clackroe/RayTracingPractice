#include <color.hpp>
#include <iostream>
#include <vec3.hpp>

struct Image {
    int Width = 256;
    int Height = 256;
};

int main()
{

    Image image;

    std::cout << "P3\n"
              << image.Width << ' ' << image.Height << "\n255\n";

    for (int j = 0; j < image.Height; j++) {
        std::clog << "\rScanlines remaining: " << (image.Height - j) << ' ' << std::flush;
        for (int i = 0; i < image.Width; i++) {
            color c = color { float(i) / (image.Width - 1), float(j) / (image.Height - 1), 0.0 };
            Color::writeColor(std::cout, c);
        }
    }
    std::clog << "\rDone.                 \n";

    return 0;
}
