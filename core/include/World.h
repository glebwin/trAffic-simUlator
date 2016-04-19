#ifndef TRAFFIC_SIMULATOR_WORLD_H
#define TRAFFIC_SIMULATOR_WORLD_H


#include <string>
#include <vector>
#include "Direction.h"
#include "Side.h"

class Car;
class Crossroad;
class Lane;
class Road;

class World {
private:

    std::vector<Car*> cars;
    std::vector<Crossroad*> crossroads;
    std::vector<Road*> roads;
    std::vector<std::pair<Road*, Side>> spawn_roads;

public:

    void on_tick(unsigned int delta_ms);

    void add_car(Car *car);
    void add_crossroad(Crossroad *crossroad);
    void add_road(Road *road);
    void add_spawn(Road *road, Side side);

    void read_file(std::string file_name);

private:

    void get_road_sides(Crossroad *beg_crossroad, Crossroad *end_crossroad, Side &beg_side, Side &end_side);
    Car* gen_rand_car();
    void gen_rand_route(Road *road, Side side, std::vector<Direction> &route);
};

#endif
