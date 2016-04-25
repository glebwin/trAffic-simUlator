#ifndef TRAFFIC_SIMULATOR_ROADVISUAL_H
#define TRAFFIC_SIMULATOR_ROADVISUAL_H


#include <SFML/Graphics.hpp>
class Road;

class RoadVisual {
private:

    sf::RenderWindow *window;
    const Road *road;

    sf::RectangleShape sprite_asphalt;
    sf::RectangleShape sprite_solid_lane;

public:

    RoadVisual(sf::RenderWindow *window, const Road *road);
    void draw();

private:

    void set_sprite_asphalt();
    void set_sprite_solid_lane();
};


#endif
