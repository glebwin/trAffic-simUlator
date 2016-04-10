#include "../include/Lane.h"
#include "../include/Road.h"

Lane::Lane(Road *road, int lane_num)
        : road(road), lane_num(lane_num) {
}

Crossroad* Lane::get_next_crossroad() {
    return road->get_next_crossroad();
}

Side Lane::get_beg_side() {
    return road->get_beg_side();
}

Side Lane::get_end_side() {
    return road->get_end_side();
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
