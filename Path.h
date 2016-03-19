#ifndef TRAFFIC_SIMULATOR_PATH_H
#define TRAFFIC_SIMULATOR_PATH_H


class Car;

class Path {
public:

    virtual Car* get_next_car(Car *car) = 0;
};


#endif
