#include "metrics.h"

const float EARTH_RADIOUS = 6369539.549050032;

inline float get_distance(const Node *const from, const Node *const to) {
    ASSERT(from != NULL);
    ASSERT(to != NULL);

    const float lat_from = from->lat;
    const float lat_to = to->lat;
    const float lon_from = from->lon;
    const float lon_to = to->lon;

    const float result = sinf(lat_from) * sinf(lat_to)
        + cosf(lat_from) * cosf(lat_to) * cosf(lon_to - lon_from);

    if(result >= 1) {
        return 0;
    } else if(result <= -1) {
        return M_PI * EARTH_RADIOUS;
    }

    return acos(result) * EARTH_RADIOUS;
}

inline float get_heuristic(const Node *const from, const Node *const to) {
    ASSERT(from != NULL);
    ASSERT(to != NULL);

    return get_distance(from, to);
}
