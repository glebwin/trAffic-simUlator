#ifndef TRAFFIC_SIMULATOR_VISUALIZER_H
#define TRAFFIC_SIMULATOR_VISUALIZER_H


#include <SFML/Graphics.hpp>
#include "../../core/include/World.h"

class Visualizer {
private:

    sf::Window *window;
    World *world;

public:

    int run();
};


#endif
