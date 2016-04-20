#ifndef TRAFFIC_SIMULATOR_CROSSROAD_H
#define TRAFFIC_SIMULATOR_CROSSROAD_H


#include <utility>
#include "Side.h"
#include "TrafficLight.h"

class Lane;
class Road;
class TrafficLight;

class Crossroad {
private:

    Road *roads[static_cast<int>(Side::SIDES_NUM)];
    TrafficLight *traffic_light;

    std::pair<int, int> top_left_corner;
    std::pair<int, int> bott_right_corner;

public:

    Crossroad(std::pair<int, int> top_left_corner, std::pair<int, int> bott_right_corner);

    void on_tick(unsigned int delta_ms);
    bool is_green_light(Lane *source, Lane *target);

    void set_traffic_light(TrafficLight *traffic_light_);

    Road* get_road(Side side);

    std::pair<int, int> get_top_left_corner() const;
    std::pair<int, int> get_bott_right_corner() const;
};


#endif
