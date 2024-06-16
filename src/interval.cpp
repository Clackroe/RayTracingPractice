#include <core.hpp>
#include <interval.hpp>

Interval::Interval()
    : min(+infinity)
    , max(-infinity) {};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);
