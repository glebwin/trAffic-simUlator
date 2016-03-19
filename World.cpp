#include "World.h"

void World::on_tick(unsigned int delta_ms) {
    for(auto it : cars)
        it->on_tick(delta_ms);
    for(auto it : crossroads)
        it->on_tick(delta_ms);
}
