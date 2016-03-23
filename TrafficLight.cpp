#include "TrafficLight.h"

void TrafficLight::on_tick(unsigned int delta_ms) {
    timer += delta_ms;
    if(timer >= schedule_it->duration) {
        timer -= schedule_it->duration;
        ++schedule_it;
        if(schedule_it == schedule.end())
            schedule_it = schedule.begin();
    }
}
