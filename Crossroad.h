#ifndef TRAFFIC_SIMULATOR_CROSSROAD_H
#define TRAFFIC_SIMULATOR_CROSSROAD_H


#include "Road.h"
#include "TrafficLight.h"

class Crossroad {
private:

    TrafficLight *traffic_light;

public:

    void on_tick(unsigned int delta_ms);
};


#endif
