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

    CrossroadPath(Lane *source, Lane *target, Crossroad *crossroad);

    bool can_enter();
    Lane* get_target_road();
};


#endif
