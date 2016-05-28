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

    int car_counter;

    const int max_route;

    double car_velocity_min;
    double car_velocity_max;
    int car_length_min;
    int car_length_max;
    int car_min_gap_min;
    int car_min_gap_max;
    int car_time_headway_min;
    int car_time_headway_max;
    double car_cruise_speed_min;
    double car_cruise_speed_max;
    double car_max_acceleration_min;
    double car_max_acceleration_max;
    double car_max_deceleration_min;
    double car_max_deceleration_max;

public:

    World();
    ~World();

    void on_tick(unsigned int delta_ms);

    void add_car(Car *car);
    void add_crossroad(Crossroad *crossroad);
    void add_road(Road *road);
    void add_spawn(Road *road, Side side);

    void read_file(std::string file_name);

    const std::vector<Car*>& get_cars();
    const std::vector<Crossroad*>& get_crossroads();
    const std::vector<Road*>& get_roads();

private:

    void get_road_sides(Crossroad *beg_crossroad, Crossroad *end_crossroad, Side &beg_side, Side &end_side);
    Car* gen_rand_car();
    void gen_rand_route(const Road *road, Side side, std::vector<Direction> &route);
};

#endif
