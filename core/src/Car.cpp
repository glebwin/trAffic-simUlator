#include <cmath>
#include "../include/Car.h"
#include "../include/Crossroad.h"
#include "../include/Lane.h"
#include "../include/Road.h"
#include "../include/Utility.h"

const double Car::min_acceleration = -1000;

Car::Car(double velocity, int length, int min_gap, int time_headway, double cruise_speed, double max_acceleration,
         double max_deceleration, Lane *lane, std::vector<Direction> &route_, int id)
        : velocity(velocity), length(length), min_gap(min_gap), time_headway(time_headway),
          cruise_speed(cruise_speed), max_acceleration(max_acceleration), max_deceleration(max_deceleration),
          lane(lane), route(route_),
          coord(0), acceleration_exponent(4), state(MOVING_STRAIGHT), id(id) {
    route_it = route.begin();
    crossroad = lane->get_next_crossroad();
    next_lane = choose_next_lane();
    lane->arrive(this);
}

void Car::on_tick(unsigned int delta_ms) {
    if(state == DROVE_AWAY)  return;

    double acceleration = calc_acceleration();
    if(acceleration < min_acceleration) {
        acceleration = 0;
        velocity = 0;
    }
    coord += velocity * static_cast<int>(delta_ms) + 0.5 * acceleration * std::pow(delta_ms, 2);
    velocity += acceleration * delta_ms;

    if(state == MOVING_STRAIGHT && coord >= lane->get_length()
       && lane->get_next_crossroad()->is_green_light(lane, next_lane)) {
        if(next_lane) {
            coord -= lane->get_length();
            lane->depart(this);
            next_lane->arrive(this);
            lane = next_lane;
            crossroad = lane->get_next_crossroad();
            route_it++;
            next_lane = choose_next_lane();
        }
        else {
            lane->depart(this);
            state = DROVE_AWAY;
        }
    }
}

bool Car::drove_away() {
    return state == DROVE_AWAY;
}

double Car::calc_acceleration() {
    double free_road_term = 0;
    double interaction_term = 0;
    double traffic_light_term = 0;

    free_road_term = std::pow(velocity / cruise_speed, acceleration_exponent);

    Car *next_car = get_next_car();
    if(next_car) {
        int next_car_dist = next_car->coord - next_car->length - coord
                            + (next_car->get_lane() != lane) * lane->get_length();
        interaction_term = std::pow(
                               (min_gap + velocity * time_headway + velocity * (velocity - next_car->velocity) /
                                     (2 * std::sqrt(max_acceleration * max_deceleration))) /
                                   next_car_dist,
                                2);
    }

    if(state == MOVING_STRAIGHT && !crossroad->is_green_light(lane, next_lane))
        traffic_light_term = std::pow((1 + velocity * time_headway + std::pow(velocity, 2) / (2 * max_deceleration))
                                      / (lane->get_length() - coord), 2);

    double acceleration = max_acceleration * (1 - free_road_term - interaction_term - traffic_light_term);

    return acceleration;
}

Car* Car::get_next_car() {
    Car *ret = nullptr;

    if(state == MOVING_STRAIGHT) {
        ret = lane->get_next_car(this);
        if(!ret && next_lane)
            ret = next_lane->get_first_car();
    }

    return ret;
}

Lane* Car::choose_next_lane() {
    if(route_it == route.end())
        return nullptr;
    Side targ_side = Utility::turn(lane->get_end_side(), *route_it);
    return crossroad->get_road(targ_side)->get_lane(Utility::opposite(targ_side), lane->get_num());
}

int Car::get_lane_coord() const {
    return coord;
}

int Car::get_length() const {
    return length;
}

int Car::get_id() const {
    return id;
}

Lane* Car::get_lane() const {
    return lane;
}
