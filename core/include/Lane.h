#ifndef TRAFFIC_SIMULATOR_LANE_H
#define TRAFFIC_SIMULATOR_LANE_H


#include <list>
#include "Side.h"


class Car;
class Crossroad;
class Road;

class Lane {
private:

    Road *road;
    int lane_num;
    Lane *left_adjacent;
    Lane *right_adjacent;

    std::list<Car*> cars;

public:

    Lane(Road *road, int lane_num);

    Crossroad* get_next_crossroad();

    Side get_beg_side();
    Side get_end_side();
    int get_num();
    Lane* get_left_adjacent();
    Lane* get_right_adjacent();

    void set_left_adjacent(Lane *lane);
    void set_right_adjacent(Lane *lane);

    int get_length();
    Car* get_next_car(Car *car);
    Car* get_first_car();
    void arrive(Car *car);
    void depart(Car *car);
    bool is_hor();

    std::pair<int, int> get_beg();
    std::pair<int, int> get_end();
};


#endif
