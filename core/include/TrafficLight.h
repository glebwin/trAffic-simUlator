#ifndef TRAFFIC_SIMULATOR_TRAFFICLIGHT_H
#define TRAFFIC_SIMULATOR_TRAFFICLIGHT_H


#include <vector>
#include "Side.h"

class TrafficLight {
public:

    struct ScheduleUnit {
        unsigned int state;
        unsigned int duration;
        ScheduleUnit(unsigned int state, unsigned int duration) : state(state), duration(duration) {}
    };

private:

    std::vector<ScheduleUnit> schedule;
    std::vector<ScheduleUnit>::iterator schedule_it;
    unsigned int timer;

public:

    TrafficLight(std::vector<ScheduleUnit> &schedule);

    void start();
    void on_tick(unsigned int delta_ms);
    bool is_green_light(Side source, Side target);

private:

    unsigned int get_mask(Side source, Side target);
};


#endif
