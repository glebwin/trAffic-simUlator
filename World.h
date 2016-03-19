#ifndef TRAFFIC_SIMULATOR_WORLD_H
#define TRAFFIC_SIMULATOR_WORLD_H


#include "Car.h"
#include "Crossroad.h"
#include <vector>

class World {
private:

    std::vector<Car *> cars;
    std::vector<Crossroad *> crossroads;

public:

    void on_tick(unsigned int delta_ms);
};

#endif
