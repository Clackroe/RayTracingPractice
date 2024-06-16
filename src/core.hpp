#ifndef RT_COREH
#define RT_COREH

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <vector>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline float randomFloat()
{
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float randomFloat(float min, float max)
{
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return min + (max - min) * distribution(generator);
}

#include <color.hpp>
#include <ray.hpp>
#include <vec3.hpp>

#include <interval.hpp>

#endif
