#include "../include/Car.h"
#include "../include/Crossroad.h"
#include "../include/World.h"

void World::on_tick(unsigned int delta_ms) {
    for(auto it : cars)
        it->on_tick(delta_ms);
    for(auto it : crossroads)
        it->on_tick(delta_ms);
}

void World::add_car(Car *car) {
    cars.push_back(car);
}

void World::add_crossroad(Crossroad *crossroad) {
    crossroads.push_back(crossroad);
}

void World::add_road(Road *road) {
    roads.push_back(road);
}
