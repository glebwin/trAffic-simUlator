#ifndef TRAFFIC_SIMULATOR_CROSSROAD_H
#define TRAFFIC_SIMULATOR_CROSSROAD_H


#include <utility>
#include "Side.h"
#include "TrafficLight.h"

class CrossroadPath;
class Lane;
class Road;
class TrafficLight;

class Crossroad {
private:

    Road *roads[SIDES_NUM];
    TrafficLight *traffic_light;
    CrossroadPath **crossroad_paths;

    std::pair<int, int> top_left_corner;
    std::pair<int, int> bott_right_corner;

public:

    Crossroad(std::pair<int, int> top_left_corner, std::pair<int, int> bott_right_corner);

    void on_tick(unsigned int delta_ms);
    bool is_green_light(Lane *source, Lane *target);
    CrossroadPath* get_crossroad_path(Side beg_side, int beg_lane_num, Side end_side, int end_lane_num);

    void set_traffic_light(TrafficLight *traffic_light_);

    std::pair<int, int> get_top_left_corner();
    std::pair<int, int> get_bott_right_corner();
};


#endif
