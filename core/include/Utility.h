#ifndef TRAFFIC_SIMULATOR_UTILITY_H
#define TRAFFIC_SIMULATOR_UTILITY_H

#include "Direction.h"
#include "Side.h"

namespace Utility {
    Side turn(Side turn_side, Direction turn_dir);
    Side opposite(Side side);
    int random(int a, int b);
    double random(double a, double b, int prec);
}

#endif
