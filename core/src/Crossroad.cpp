#include "../include/Crossroad.h"
#include "../include/Lane.h"
#include "../include/TrafficLight.h"

Crossroad::Crossroad(std::pair<int, int> top_left_corner, std::pair<int, int> bott_right_corner)
        : top_left_corner(top_left_corner), bott_right_corner(bott_right_corner),
          traffic_light(nullptr) {
    for(int i = 0; i < SIDES_NUM; i++)
        roads[i] = nullptr;
}

void Crossroad::on_tick(unsigned int delta_ms) {
    if(traffic_light)
        traffic_light->on_tick(delta_ms);
}

bool Crossroad::is_green_light(Lane *source, Lane *target) {
    return !(traffic_light && target) || traffic_light->is_green_light(source->get_end_side(), target->get_beg_side());
}

Road *Crossroad::get_road(Side side) {
    return roads[side];
}

void Crossroad::set_traffic_light(TrafficLight *traffic_light_) {
    traffic_light = traffic_light_;
}

std::pair<int, int> Crossroad::get_top_left_corner() const {
    return top_left_corner;
}

std::pair<int, int> Crossroad::get_bott_right_corner() const {
    return bott_right_corner;
}
