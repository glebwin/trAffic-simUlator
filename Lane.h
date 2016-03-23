#ifndef TRAFFIC_SIMULATOR_LANE_H
#define TRAFFIC_SIMULATOR_LANE_H


#include <list>

class Car;

class Lane {
private:

    int length;
    std::list<Car*> cars;

public:

    int get_length() const;
};


#endif
