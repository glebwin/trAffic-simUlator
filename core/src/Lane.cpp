#include "../include/Lane.h"
#include "../include/Road.h"

Side Lane::get_beg_side() {
    return road->get_beg_side();
}

Side Lane::get_end_side() {
    return road->get_end_side();
}

Crossroad* Lane::get_next_crossroad() {
    return road->get_next_crossroad();
}

int Lane::get_num() {
    return lane_num;
}
