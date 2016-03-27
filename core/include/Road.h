#ifndef TRAFFIC_SIMULATOR_ROAD_H
#define TRAFFIC_SIMULATOR_ROAD_H


#include <vector>
#include "Side.h"

class Crossroad;
class Lane;

class Road {
private:

    std::vector<Lane*> lanes;
    Side beginning_side;
    Side end_side;
    Crossroad *beginning_crossroad;
    Crossroad *end_crossroad;

public:

    Side get_beg_side();
    Side get_end_side();
    Crossroad* get_next_crossroad();

    ~Road();
};


#endif
