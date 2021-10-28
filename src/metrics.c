#include "metrics.h"

const double EARTH_RADIOUS = 6371000;

double get_distance(const Node *from, const Node *to) {
    const double lat_from = from->lat;
    const double lat_to = to->lat;
    const double lon_from = from->lon;
    const double lon_to = to->lon;

    return acos(sin(lat_from)*sin(lat_to) + cos(lat_from)*cos(lat_to)*cos(lon_to-lon_from)) * EARTH_RADIOUS;
}

double get_heuristic(const Node *from, const Node *to) {
    return get_distance(from, to);
}
