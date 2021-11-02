#include "metrics.h"

const double EARTH_RADIOUS = 6371000;

double get_distance(const Node *from, const Node *to) {
    ASSERT(from != NULL);
    ASSERT(to != NULL);

    const double lat_from = from->lat;
    const double lat_to = to->lat;
    const double lon_from = from->lon;
    const double lon_to = to->lon;

    const double result = sin(lat_from)*sin(lat_to) + cos(lat_from)*cos(lat_to)*cos(lon_to-lon_from);

    if(result >= 1) {
        return 0;
    } else if(result <= -1) {
        return M_PI * EARTH_RADIOUS;
    }

    return acos(result) * EARTH_RADIOUS;
}

double get_heuristic(const Node *from, const Node *to) {
    ASSERT(from != NULL);
    ASSERT(to != NULL);

    return get_distance(from, to);
}
