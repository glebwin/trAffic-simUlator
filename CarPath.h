#ifndef TRAFFIC_SIMULATOR_CARPATH_H
#define TRAFFIC_SIMULATOR_CARPATH_H


#include <list>

class Car;

class CarPath {
private:

    int length;
    std::list<Car*> cars;

public:

    int get_length() const;
    Car* get_next_car(Car *car) const;
    Car* get_first_car() const;
};


#endif
