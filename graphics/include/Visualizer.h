#ifndef TRAFFIC_SIMULATOR_VISUALIZER_H
#define TRAFFIC_SIMULATOR_VISUALIZER_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "../../core/include/World.h"

class CarVisual;
class CrossroadVisual;
class RoadVisual;

class Visualizer {
private:

    sf::RenderWindow *window;
    World &world;

    std::vector<CarVisual*> cars;
    std::vector<CrossroadVisual*> crossroads;
    std::vector<RoadVisual*> roads;

public:

    Visualizer(World &world);

    int run();

private:

    void handle_event(sf::Event &event);
    void draw();
    void update_cars();
};


#endif
