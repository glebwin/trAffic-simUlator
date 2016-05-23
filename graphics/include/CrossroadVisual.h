#ifndef TRAFFIC_SIMULATOR_CROSSROADVISUAL_H
#define TRAFFIC_SIMULATOR_CROSSROADVISUAL_H


#include <SFML/Graphics.hpp>
class Crossroad;

class CrossroadVisual {
private:

    sf::RenderWindow &window;
    const Crossroad &crossroad;
    sf::RectangleShape sprite;

public:

    CrossroadVisual(sf::RenderWindow &window, const Crossroad &crossroad);
    ~CrossroadVisual();

    void draw();
};


#endif
