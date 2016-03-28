#ifndef TRAFFIC_SIMULATOR_CROSSROAD_H
#define TRAFFIC_SIMULATOR_CROSSROAD_H


#include "Side.h"

class CrossroadPath;
class Lane;
class Road;
class TrafficLight;

class Crossroad {
private:

    Road *roads[SIDES_NUM];
    TrafficLight *traffic_light;
    CrossroadPath **crossroad_paths;

public:

    void on_tick(unsigned int delta_ms);
    bool is_green_light(Lane *source, Lane *target);
    CrossroadPath* get_crossroad_path(Side beg_side, int beg_num, Side end_side, int end_num);
};


#endif
