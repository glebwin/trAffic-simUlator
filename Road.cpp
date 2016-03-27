#include "Lane.h"
#include "Road.h"

Road::~Road() {
    for(auto lane : lanes)
        delete lane;
}

Side Road::get_beg_side() {
    return beginning_side;
}

Side Road::get_end_side() {
    return end_side;
}

Crossroad* Road::get_next_crossroad() {
    return end_crossroad;
}
