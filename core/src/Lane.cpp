#include "../include/Car.h"
#include "../include/Crossroad.h"
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
    int coord = car->get_lane_coord();
    if(cars.empty() || coord >= cars.back()->get_lane_coord()) {
        cars.insert(cars.end(), car);
        return;
    }

    for(auto it = cars.begin(); ; ++it)
        if(coord < (*it)->get_lane_coord()) {
            cars.insert(it, car);
            break;
        }
}

void Lane::depart(Car *car) {
    for(auto it = --cars.end(); ; --it)
        if(*it == car) {
            cars.erase(it);
            break;
        }
}

bool Lane::is_hor() {
    return road->is_hor();
}

std::pair<int, int> Lane::get_beg() {
    Side lane_side = road->get_beg_side(this);
    Side road_beg = road->get_beg_side();
    Side road_end = road->get_end_side();
    Crossroad *cr = road->get_next_crossroad(lane_side);
    double lane_width = static_cast<double>(road->get_width()) /
                        (road->get_forward_lanes().size() + road->get_backward_lanes().size());

    switch(lane_side) {
        case TOP:
            if(road_beg == TOP)
                return std::pair<int, int>(cr->get_top_left_corner().first +
                                           lane_width * (road->get_forward_lanes().size() - lane_num - 1) +
                                           lane_width / 2,
                                           cr->get_bott_right_corner().second);
            else
                return std::pair<int, int>(cr->get_top_left_corner().first +
                                           lane_width * (road->get_backward_lanes().size() - lane_num - 1) +
                                           lane_width / 2,
                                           cr->get_bott_right_corner().second);
        case RIGHT:
            if(road_beg == RIGHT)
                return std::pair<int, int>(cr->get_bott_right_corner().first,
                                           cr->get_top_left_corner().second +
                                           lane_width * (road->get_forward_lanes().size() - lane_num - 1) +
                                           lane_width / 2);
            else
                return std::pair<int, int>(cr->get_bott_right_corner().first,
                                           cr->get_top_left_corner().second +
                                           lane_width * (road->get_backward_lanes().size() - lane_num - 1) +
                                           lane_width / 2);
        case BOTTOM:
            if(road_beg == BOTTOM)
                return std::pair<int, int>(cr->get_top_left_corner().first +
                                           lane_width * (road->get_backward_lanes().size() + lane_num) +
                                           lane_width / 2,
                                           cr->get_top_left_corner().second);
            else
                return std::pair<int, int>(cr->get_top_left_corner().first +
                                           lane_width * (road->get_forward_lanes().size() + lane_num) +
                                           lane_width / 2,
                                           cr->get_top_left_corner().second);
        case LEFT:
            if(road_beg == LEFT)
                return std::pair<int, int>(cr->get_top_left_corner().first,
                                           cr->get_top_left_corner().second +
                                           lane_width * (road->get_backward_lanes().size() + lane_num) +
                                           lane_width / 2);
            else
                return std::pair<int, int>(cr->get_top_left_corner().first,
                                           cr->get_top_left_corner().second +
                                           lane_width * (road->get_forward_lanes().size() + lane_num) +
                                           lane_width / 2);
    }
}

std::pair<int, int> Lane::get_end() {
    std::pair<int, int> res = get_beg();
    Side side = road->get_beg_side(this);
    switch(side) {
        case TOP:
            res.second += road->get_length();
            break;
        case RIGHT:
            res.first  -= road->get_length();
            break;
        case BOTTOM:
            res.second -= road->get_length();
            break;
        case LEFT:
            res.first  += road->get_length();
            break;
    }
    return res;
}
