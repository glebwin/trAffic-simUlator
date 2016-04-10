#include "../include/Lane.h"
#include "../include/Road.h"

Road::Road(Crossroad *beg_crossroad, Side beg_side, Crossroad *end_crossroad, Side end_side,
           unsigned int forward_lanes_num, unsigned int backward_lanes_num)
        : beg_crossroad(beg_crossroad), beg_side(beg_side), end_crossroad(end_crossroad), end_side(end_side) {
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

Crossroad* Road::get_next_crossroad() {
    return end_crossroad;
}
