#ifndef TRAFFIC_SIMULATOR_ROADVISUAL_H
#define TRAFFIC_SIMULATOR_ROADVISUAL_H


#include <vector>
#include <SFML/Graphics.hpp>
class Road;

class RoadVisual {
private:

    sf::RenderWindow &window;
    const Road &road;

    sf::RectangleShape sprite_asphalt;
    sf::RectangleShape sprite_solid_line;
    sf::RectangleShape sprite_dashed_line;
    std::vector<double> dashed_line_xs;
    std::vector<double> dashed_line_ys;

public:

    RoadVisual(sf::RenderWindow &window, const Road &road);
    void draw();

private:

    void set_sprite_asphalt();
    void set_sprite_solid_line();
    void set_sprites_dashed_lines();
};


#endif
