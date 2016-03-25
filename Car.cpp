#include <cmath>
#include "Car.h"
#include "CrossRoadPath.h"
#include "Lane.h"

void Car::on_tick(unsigned int delta_ms) {
    if(state == DROVE_AWAY)  return;

    double acceleration = calc_acceleration();
    coord += velocity * static_cast<int>(delta_ms) + 0.5 * acceleration * pow(delta_ms, 2);
    velocity += acceleration * delta_ms;
}

double Car::calc_acceleration() {
    double free_road_term = 0;
    double interaction_term = 0;
    double crossroad_term = 0;

    free_road_term = pow(static_cast<double>(velocity) / cruise_speed, acceleration_exponent);

    Car *next_car = get_next_car();
    if(next_car)
        interaction_term = pow(
                               (min_gap + static_cast<double>(velocity)*time_headway + static_cast<double>(velocity)*(velocity-next_car->velocity) / (2*sqrt(static_cast<double>(max_acceleration)*max_deceleration))) /
                                   (next_car->coord - next_car->length - coord),
                                2);

//    if(state == MOVING_STRAIGHT && )
//        crossroad_term = pow((1 + (double)velocity*time_headway + pow((double)velocity, 2) / (2 * max_deceleration)) / (path->get_length() - coord), 2);


    double acceleration = max_acceleration * (1 - free_road_term - interaction_term - crossroad_term);

    return acceleration;
}

Car* Car::get_next_car() {
    Car *ret = nullptr;

    if(state == MOVING_STRAIGHT) {
        ret = lane->get_next_car(this);
        if (!ret)
            ret = crossroad_path->get_first_car();
    }
    else {
        ret = crossroad_path->get_next_car(this);
        if (!ret && lane)
            ret = lane->get_first_car();
    }

    return ret;
}
