#ifndef RT_COLORH
#define RT_COLORH
#include <interval.hpp>
#include <iostream>
#include <vec3.hpp>

using color = Vec3;

static inline float linearToGamma(float x)
{
    if (x > 0) {
        return std::sqrt(x);
    }
    return 0;
};

namespace Color {

inline void writeColor(std::ostream& out, const color& col)
{
    float r = col.getX();
    float g = col.getY();
    float b = col.getZ();

    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    static const Interval intensity(0, 0.999);
    // Convert to [0, 255]
    int rr = int(256 * intensity.clamp(r));
    int gg = int(256 * intensity.clamp(g));
    int bb = int(256 * intensity.clamp(b));
    out << rr << ' ' << gg << ' ' << bb << '\n';
}
}

#endif
