#ifndef TRAFFIC_SIMULATOR_WORLD_H
#define TRAFFIC_SIMULATOR_WORLD_H


#include <vector>
#include "Car.h"
#include "Crossroad.h"

class World {
private:

    std::vector<Car *> cars;
    std::vector<Crossroad *> crossroads;

public:

    void on_tick(unsigned int delta_ms);
};

#endif
