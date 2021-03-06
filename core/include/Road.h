#ifndef TRAFFIC_SIMULATOR_ROAD_H
#define TRAFFIC_SIMULATOR_ROAD_H


#include <vector>
#include "Side.h"

class Crossroad;
class Lane;

class Road {
private:

    std::vector<Lane*> forward_lanes;
    std::vector<Lane*> backward_lanes;
    Side beg_side;
    Side end_side;
    Crossroad *beg_crossroad;
    Crossroad *end_crossroad;

    int length;

public:

    Road(Crossroad *beg_crossroad, Side beg_side, Crossroad *end_crossroad, Side end_side,
         unsigned int forward_lanes_num, unsigned int backward_lanes_num);
    ~Road();

    Side get_beg_side();
    Side get_end_side();
    Side get_beg_side(Lane *lane);
    Side get_end_side(Lane *lane);
    Crossroad* get_next_crossroad(Side side) const;
    Crossroad* get_beg_crossroad() const;
    Crossroad* get_end_crossroad() const;
    const std::vector<Lane*>& get_forward_lanes() const;
    const std::vector<Lane*>& get_backward_lanes() const;
    Lane* get_rand_lane(Side side);
    Lane* get_lane(Side side, int num);
    int get_length();
    bool is_hor();
    int get_width();

private:

    void calc_length(Crossroad *crossroad1, Crossroad *crossroad2);
    void create_lanes(std::vector<Lane*> &lanes, unsigned int lanes_num);
};


#endif
