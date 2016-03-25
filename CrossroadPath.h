#ifndef TRAFFIC_SIMULATOR_CROSSROADPATH_H
#define TRAFFIC_SIMULATOR_CROSSROADPATH_H


#include "CarPath.h"

class Crossroad;
class Lane;

class CrossroadPath : public CarPath {
private:

    Lane *source;
    Lane *target;

    Crossroad *crossroad;

public:

    bool can_enter();

    CrossroadPath(Lane *source, Lane *target, Crossroad *crossroad);
};


#endif
