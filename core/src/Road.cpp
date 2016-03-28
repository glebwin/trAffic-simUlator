#include "../include/Lane.h"
#include "../include/Road.h"

Road::Road(Crossroad *beg_crossroad, Side beg_side, Crossroad *end_crossroad, Side end_side)
        : beg_crossroad(beg_crossroad), beg_side(beg_side), end_crossroad(end_crossroad), end_side(end_side) {
    unsigned int lanes_num = 0;
    lanes.resize(lanes_num);
    for(int i = 0; i < lanes_num; i++)
        lanes.push_back(new Lane(this, i));
}

Road::~Road() {
    for(auto lane : lanes)
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
