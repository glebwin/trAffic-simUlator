#include "../include/CarPath.h"

int CarPath::get_length() const {
    return length;
}

Car* CarPath::get_next_car(Car *car) const {
    if(car == cars.back())
        return nullptr;

    for(auto it = cars.begin(); ; ++it)
        if(*it == car)
            return *(++it);
}

Car* CarPath::get_first_car() const {
    if(!cars.empty())
        return *cars.begin();
    else
        return nullptr;
}

void CarPath::arrive(Car *car) {
    cars.push_front(car);
}

void CarPath::depart(Car *car) {
    for(auto it = --cars.end(); ; --it)
        if(*it == car) {
            cars.erase(it);
            break;
        }
}
