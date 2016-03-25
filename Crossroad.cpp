#include "Crossroad.h"

void Crossroad::on_tick(unsigned int delta_ms) {
    traffic_light->on_tick(delta_ms);
}

bool Crossroad::is_green_light(Lane *source, Lane *target) {
    return traffic_light->is_green_light(source->get_end_side(), target->get_beginning_side());
}
