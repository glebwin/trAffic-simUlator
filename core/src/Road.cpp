#include <algorithm>
#include "../include/Crossroad.h"
#include "../include/Lane.h"
#include "../include/Road.h"

Road::Road(Crossroad *beg_crossroad, Side beg_side, Crossroad *end_crossroad, Side end_side,
           unsigned int forward_lanes_num, unsigned int backward_lanes_num)
        : beg_crossroad(beg_crossroad), beg_side(beg_side), end_crossroad(end_crossroad), end_side(end_side) {
    calc_length(beg_crossroad, end_crossroad);
    forward_lanes.reserve(forward_lanes_num);
    for(int i = 0; i < forward_lanes_num; i++)
        forward_lanes.push_back(new Lane(this, i));
    backward_lanes.reserve(backward_lanes_num);
    for(int i = 0; i < backward_lanes_num; i++)
        backward_lanes.push_back(new Lane(this, i));
}

Road::~Road() {
    for(auto lane : forward_lanes)
        delete lane;
    for(auto lane : backward_lanes)
        delete lane;
}

Side Road::get_beg_side() {
    return beg_side;
}

Side Road::get_end_side() {
    return end_side;
}

Side Road::get_beg_side(Lane *lane) {
    if(lane->get_num() < forward_lanes.size() && lane == forward_lanes[lane->get_num()])
        return beg_side;
    else
        return end_side;
}

Side Road::get_end_side(Lane *lane) {
    if(lane->get_num() < forward_lanes.size() && lane == forward_lanes[lane->get_num()])
        return end_side;
    else
        return beg_side;
}

Crossroad* Road::get_next_crossroad(Side side) {
    if(side == end_side)
        return end_crossroad;
    else
        return beg_crossroad;
}

Crossroad *Road::get_beg_crossroad() const {
    return beg_crossroad;
}

Crossroad *Road::get_end_crossroad() const {
    return end_crossroad;
}

const std::vector<Lane *>& Road::get_forward_lanes() const {
    return forward_lanes;
}

const std::vector<Lane *>& Road::get_backward_lanes() const {
    return backward_lanes;
}

Lane *Road::get_rand_lane(Side side) {
    if(side == beg_side)
        return forward_lanes[rand() % forward_lanes.size()];
    else
        return backward_lanes[rand() % backward_lanes.size()];
}

Lane* Road::get_lane(Side side, int num) {
    if (side == beg_side) {
        return forward_lanes[num];
    }
    else {
        return backward_lanes[num];
    }
}

int Road::get_length() {
    return length;
}

void Road::calc_length(Crossroad *crossroad1, Crossroad *crossroad2) {
    auto tl1 = crossroad1->get_top_left_corner();
    auto br1 = crossroad1->get_bott_right_corner();
    auto tl2 = crossroad2->get_top_left_corner();
    auto br2 = crossroad2->get_bott_right_corner();
    if(is_hor())
        length = std::max(tl2.first - br1.first, tl1.first - br2.first);
    else
        length = std::max(tl2.second - br1.second, tl1.second - br2.second);
}

bool Road::is_hor() {
    return beg_crossroad->get_top_left_corner().second == end_crossroad->get_top_left_corner().second;
}

int Road::get_width() {
    switch(beg_side) {
        case TOP:
            return end_crossroad->get_top_left_corner().second - beg_crossroad->get_bott_right_corner().second;
        case RIGHT:
            return beg_crossroad->get_top_left_corner().first - end_crossroad->get_bott_right_corner().first;
        case BOTTOM:
            return beg_crossroad->get_top_left_corner().second - end_crossroad->get_bott_right_corner().second;
        case LEFT:
            return end_crossroad->get_top_left_corner().first - beg_crossroad->get_bott_right_corner().first;
    }
}
