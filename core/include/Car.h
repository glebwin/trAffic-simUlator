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
    double max_acceleration;
    double max_deceleration;
    int acceleration_exponent;

    State state;
    Lane *lane;
    Lane *next_lane;
    Crossroad *crossroad;

    std::vector<Direction> route;
    std::vector<Direction>::iterator route_it;

    int id;

public:

    Car(int velocity, int length, int min_gap, int time_headway, int cruise_speed,
        double max_acceleration, double max_deceleration, Lane *lane, std::vector<Direction> &route, int id);

    void on_tick(unsigned int delta_ms);
    bool drove_away();
    int get_lane_coord() const;
    int get_length() const;
    int get_id() const;
    Lane* get_lane() const;

private:

    double calc_acceleration();
    Car* get_next_car();
    Lane* choose_next_lane();
};


#endif
