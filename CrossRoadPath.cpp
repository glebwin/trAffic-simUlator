#include "Crossroad.h"
#include "CrossRoadPath.h"

bool CrossRoadPath::can_enter() {
    return cross_road->is_green_light(source, target);
}
