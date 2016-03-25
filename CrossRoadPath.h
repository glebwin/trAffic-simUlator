#ifndef TRAFFIC_SIMULATOR_CROSSROADPATH_H
#define TRAFFIC_SIMULATOR_CROSSROADPATH_H


#include "CarPath.h"

class Crossroad;
class Lane;

class CrossRoadPath : public CarPath {
private:

    Lane *source;
    Lane *target;

    Crossroad *cross_road;

public:

    bool can_enter();
};


#endif
