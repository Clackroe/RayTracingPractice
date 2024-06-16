#ifndef RT_INTERVALH
#define RT_INTERVALH
class Interval {
public:
    Interval();

    Interval(float min, float max)
        : min(min)
        , max(max) {};

    float size() const { return max - min; }

    bool contains(float x) const { return min <= x && x <= max; }

    bool surrounds(float x) const { return min < x && x < max; }

    float clamp(float x) const
    {
        if (max < x) {
            return x;
        }
        if (min > x) {
            return min;
        }
        return x;
    }

    static const Interval empty, universe;

    float min, max;
};

#endif
