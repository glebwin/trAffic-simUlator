#include <cmath>
#include "Car.h"

void Car::on_tick(unsigned int delta_ms) {
    double acceleration = calc_acceleration();
    velocity += acceleration * delta_ms;
}

double Car::calc_acceleration() {
    Car *next_car = path->get_next_car(this);

    double free_road_term = pow((double)velocity / cruise_speed, acceleration_exponent);
    double interaction_term = pow(
                              (min_gap + velocity*time_headway + velocity*(velocity-next_car->velocity) / (2*sqrt(max_acceleration*max_deceleration))) /
                                  (next_car->coord - next_car->length - coord),
                              2);

    double acceleration = max_acceleration * (1 - free_road_term - interaction_term);

    return acceleration;
}
