#include "Crossroad.h"

void Crossroad::on_tick(unsigned int delta_ms) {
    traffic_light->on_tick(delta_ms);
}

bool Crossroad::can_enter_crossroad() {
    return false;
}
