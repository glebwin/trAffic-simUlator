#ifndef TRAFFIC_SIMULATOR_LANE_H
#define TRAFFIC_SIMULATOR_LANE_H


#include "CarPath.h"
#include "Side.h"


class Crossroad;

class Road;

class Lane : public CarPath {
private:

    Road *road;
    int lane_num;

public:

    Side get_beg_side();
    Side get_end_side();
    Crossroad* get_next_crossroad();
    int get_num();
};


#endif
