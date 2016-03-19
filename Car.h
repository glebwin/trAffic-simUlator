#ifndef TRAFFIC_SIMULATOR_CAR_H
#define TRAFFIC_SIMULATOR_CAR_H


#include <vector>
#include "Path.h"
#include "Road.h"

class Car {
private:

    int velocity;
    int coord;

    int length;
    int min_gap;
    int time_headway;
    int cruise_speed;
    int max_acceleration;
    int max_deceleration;
    int acceleration_exponent;

    Path *path;
    std::vector<Road *> route;

public:

    void on_tick(unsigned int delta_ms);

private:

    double calc_acceleration();
};


#endif
