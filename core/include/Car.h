#ifndef TRAFFIC_SIMULATOR_CAR_H
#define TRAFFIC_SIMULATOR_CAR_H


#include <vector>
#include "Direction.h"
#include "Side.h"

class Crossroad;
class Lane;

class Car {

    enum State {MOVING_STRAIGHT, CHANGING_LANE, CROSSING_CROSSROAD, DROVE_AWAY, STATES_NUM};

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

    State state;
    Lane *lane;
    Lane *next_lane;
    Crossroad *crossroad;

    std::vector<Direction> route;
    std::vector<Direction>::iterator route_it;

public:

    void on_tick(unsigned int delta_ms);

private:

    double calc_acceleration();
    Car* get_next_car();
    Lane* choose_next_lane();
};


#endif
