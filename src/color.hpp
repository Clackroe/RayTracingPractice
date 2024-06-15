#ifndef RT_COLORH
#define RT_COLORH
#include <strstream>
#include <vec3.hpp>

using color = vec3;

namespace Color {

void writeColor(std::ostream& out, const color& col)
{
    float r = col.getX();
    float g = col.getY();
    float b = col.getZ();

    // Convert to [0, 255]
    int rr = int(255.999 * r);
    int gg = int(255.999 * g);
    int bb = int(255.999 * b);
    out << rr << ' ' << gg << ' ' << bb << '\n';
}
}

#endif
