#ifndef TRAFFIC_SIMULATOR_CROSSROADPATH_H
#define TRAFFIC_SIMULATOR_CROSSROADPATH_H


#include <list>
#include "Car.h"

class CrossRoadPath {
private:

    int length;
    std::list<Car*> cars;
    Lane *source;
    Lane *target;

public:

    int get_length() const;
};


#endif
