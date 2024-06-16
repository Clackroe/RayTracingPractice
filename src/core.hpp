#ifndef RT_COREH
#define RT_COREH

#include <cmath>
#include <limits>
#include <memory>
#include <vector>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

#include <color.hpp>
#include <ray.hpp>
#include <vec3.hpp>

#endif
