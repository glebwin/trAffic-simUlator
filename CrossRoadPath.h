#ifndef TRAFFIC_SIMULATOR_CROSSROADPATH_H
#define TRAFFIC_SIMULATOR_CROSSROADPATH_H


#include <list>
#include "CarPath.h"

class Lane;

class CrossRoadPath : public CarPath {
private:

    Lane *source;
    Lane *target;

public:
};


#endif
