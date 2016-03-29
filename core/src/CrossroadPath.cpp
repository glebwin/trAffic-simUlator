#include "../include/Crossroad.h"
#include "../include/CrossroadPath.h"

CrossroadPath::CrossroadPath(Lane *source, Lane *target, Crossroad *crossroad)
        : source(source), target(target), crossroad(crossroad) {

}

bool CrossroadPath::can_enter() {
    return crossroad->is_green_light(source, target);
}

Lane *CrossroadPath::get_target_road() {
    return target;
}
