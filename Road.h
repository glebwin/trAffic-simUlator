#ifndef TRAFFIC_SIMULATOR_ROAD_H
#define TRAFFIC_SIMULATOR_ROAD_H


#include <vector>
#include "Lane.h"

class Road {
private:

    std::vector<Lane *> lanes;
};


#endif
