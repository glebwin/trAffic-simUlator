#ifndef TRAFFIC_SIMULATOR_LANE_H
#define TRAFFIC_SIMULATOR_LANE_H


#include "CarPath.h"
#include "Side.h"


class Lane : public CarPath {
private:

    Side beginning;
    Side end;

public:

    Side get_beginning_side();
    Side get_end_side();
};


#endif
