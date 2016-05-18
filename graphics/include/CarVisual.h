#ifndef TRAFFIC_SIMULATOR_CARVISUAL_H
#define TRAFFIC_SIMULATOR_CARVISUAL_H


#include <SFML/Graphics.hpp>

class Car;

class CarVisual {
private:

    sf::RenderWindow *window;
    const Car &car;
    int id;
    sf::RectangleShape sprite;

public:

    CarVisual(sf::RenderWindow *world, const Car &car);

    void draw();
    int get_id();

private:

    void calc_coord();
};


#endif
