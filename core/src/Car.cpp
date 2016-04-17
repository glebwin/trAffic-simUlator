#include <cmath>
#include "../include/Car.h"
#include "../include/Crossroad.h"
#include "../include/Lane.h"
#include "../include/Road.h"
#include "../include/Utility.h"

void Car::on_tick(unsigned int delta_ms) {
    if(state == DROVE_AWAY)  return;

    double acceleration = calc_acceleration();
    coord += velocity * static_cast<int>(delta_ms) + 0.5 * acceleration * pow(delta_ms, 2);
    velocity += acceleration * delta_ms;

    if(state == MOVING_STRAIGHT && coord >= lane->get_length()
       && lane->get_next_crossroad()->is_green_light(lane, next_lane)) {
        if(route_it != route.end()) {
            coord -= lane->get_length();
            lane->depart(this);
            coord -= 6000;
            next_lane->arrive(this);
            lane = next_lane;
            crossroad = lane->get_next_crossroad();
            next_lane = choose_next_lane();
            route_it++;
        }
        else {
            lane->depart(this);
            state = DROVE_AWAY;
        }
    }
}

double Car::calc_acceleration() {
    double free_road_term = 0;
    double interaction_term = 0;
    double traffic_light_term = 0;

    free_road_term = pow(static_cast<double>(velocity) / cruise_speed, acceleration_exponent);

    Car *next_car = get_next_car();
    if(next_car)
        interaction_term = pow(
                               (min_gap + static_cast<double>(velocity)*time_headway + static_cast<double>(velocity)*(velocity-next_car->velocity) / (2*sqrt(static_cast<double>(max_acceleration)*max_deceleration))) /
                                   (next_car->coord - next_car->length - coord),
                                2);

    if(state == MOVING_STRAIGHT && !crossroad->is_green_light(lane, next_lane))
        traffic_light_term = pow((1 + static_cast<double>(velocity)*time_headway + pow(velocity, 2) / (2 * max_deceleration)) / (lane->get_length() - coord), 2);

    double acceleration = max_acceleration * (1 - free_road_term - interaction_term - traffic_light_term);

    return acceleration;
}

Car* Car::get_next_car() {
    Car *ret = nullptr;

    if(state == MOVING_STRAIGHT) {
        ret = lane->get_next_car(this);
        if (!ret)
            ret = next_lane->get_first_car();
    }

    return ret;
}

Lane *Car::choose_next_lane() {
    Side targ_side = Utility::turn(lane->get_end_side(), *route_it);
    return crossroad->get_road(targ_side)->get_lane(targ_side, lane->get_num());
}
