#ifndef TRAFFIC_SIMULATOR_ROAD_H
#define TRAFFIC_SIMULATOR_ROAD_H


#include "Lane.h"
#include <vector>

class Road {
private:

    std::vector<Lane *> lanes;
};


#endif
