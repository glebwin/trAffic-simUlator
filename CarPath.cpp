#include "CarPath.h"

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
