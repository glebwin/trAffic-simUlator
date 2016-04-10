#ifndef TRAFFIC_SIMULATOR_LANE_H
#define TRAFFIC_SIMULATOR_LANE_H


#include "CarPath.h"
#include "Side.h"


class Crossroad;
class Road;

class Lane : public CarPath {
private:

    Road *road;
    int lane_num;
    Lane *left_adjacent;
    Lane *right_adjacent;

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
};


#endif
