#include "../include/Lane.h"
#include "../include/Road.h"

Lane::Lane(Road *road, int lane_num)
        : road(road), lane_num(lane_num) {
}

Crossroad* Lane::get_next_crossroad() {
    return road->get_next_crossroad(get_end_side());
}

Side Lane::get_beg_side() {
    return road->get_beg_side(this);
}

Side Lane::get_end_side() {
    return road->get_end_side(this);
}

int Lane::get_num() {
    return lane_num;
}

Lane* Lane::get_left_adjacent() {
    return left_adjacent;
}

Lane* Lane::get_right_adjacent() {
    return right_adjacent;
}

void Lane::set_left_adjacent(Lane *lane) {
    left_adjacent = lane;
}

void Lane::set_right_adjacent(Lane *lane) {
    right_adjacent = lane;
}

int Lane::get_length() {
    return road->get_length();
}

Car* Lane::get_next_car(Car *car) {
    if(car == cars.back())
        return nullptr;

    for(auto it = cars.begin(); ; ++it)
        if(*it == car)
            return *(++it);
}

Car* Lane::get_first_car() {
    if(!cars.empty())
        return *cars.begin();
    else
        return nullptr;
}

void Lane::arrive(Car *car) {
    cars.push_front(car);
}

void Lane::depart(Car *car) {
    for(auto it = --cars.end(); ; --it)
        if(*it == car) {
            cars.erase(it);
            break;
        }
}
