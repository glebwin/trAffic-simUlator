#include "../include/TrafficLight.h"

void TrafficLight::on_tick(unsigned int delta_ms) {
    timer += delta_ms;
    if(timer >= schedule_it->duration) {
        timer -= schedule_it->duration;
        ++schedule_it;
        if(schedule_it == schedule.end())
            schedule_it = schedule.begin();
    }
}

bool TrafficLight::is_green_light(Side source, Side target) {
    return static_cast<bool>(schedule_it->state & get_mask(source, target));
}

int TrafficLight::get_mask(Side source, Side target) {
    return source * Side::SIDES_NUM + target;
}
