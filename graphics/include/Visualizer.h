#ifndef TRAFFIC_SIMULATOR_VISUALIZER_H
#define TRAFFIC_SIMULATOR_VISUALIZER_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "../../core/include/World.h"

class CrossroadVisual;

class Visualizer {
private:

    sf::RenderWindow *window;
    World *world;

    std::vector<CrossroadVisual*> crossroads;

public:

    Visualizer(World *world);

    int run();

private:

    void handle_event(sf::Event &event);
    void draw();
};


#endif
