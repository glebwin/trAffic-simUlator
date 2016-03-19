#ifndef TRAFFIC_SIMULATOR_CAR_H
#define TRAFFIC_SIMULATOR_CAR_H


#include "Path.h"

class Car {
private:

    int acceleration;
    int velocity;

    int min_gap;
    int time_headway;
    int cruise_speed;
    int max_acceleration;
    int max_deceleration;
    int acceleration_exponent;

public:

    void on_tick(unsigned int delta_ms);
};


#endif
