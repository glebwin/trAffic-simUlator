#include "../include/TrafficLight.h"

TrafficLight::TrafficLight(std::vector<ScheduleUnit> &schedule)
        : schedule(schedule) {
    start();
}

void TrafficLight::on_tick(unsigned int delta_ms) {
    timer += delta_ms;
    if(timer >= schedule_it->duration) {
        timer -= schedule_it->duration;
        ++schedule_it;
        if(schedule_it == schedule.end())
            schedule_it = schedule.begin();
    }
}

void TrafficLight::start() {
    schedule_it = schedule.begin();
    timer = 0;
}

bool TrafficLight::is_green_light(Side source, Side target) {
    return static_cast<bool>(schedule_it->state & get_mask(source, target));
}

unsigned int TrafficLight::get_mask(Side source, Side target) {
    return 1 << (source * SIDES_NUM + target);
}
