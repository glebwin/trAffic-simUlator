#ifndef TRAFFIC_SIMULATOR_WORLD_H
#define TRAFFIC_SIMULATOR_WORLD_H


#include <string>
#include <vector>
#include "Side.h"

class Car;
class Crossroad;
class Road;

class World {
private:

    std::vector<Car*> cars;
    std::vector<Crossroad*> crossroads;
    std::vector<Road*> roads;

public:

    void on_tick(unsigned int delta_ms);

    void add_car(Car *car);
    void add_crossroad(Crossroad *crossroad);
    void add_road(Road *road);

    void read_file(std::string file_name);

private:

    void get_road_sides(Crossroad *beg_crossroad, Crossroad *end_crossroad, Side &beg_side, Side &end_side);
};

#endif
