#include "../../core/include/Crossroad.h"
#include "../include/CrossroadVisual.h"
#include "../include/VisualizerConsts.h"

double CrossroadVisual::outline_cf = 0.02;

CrossroadVisual::CrossroadVisual(sf::RenderWindow *window, const Crossroad *crossroad)
        : window(window), crossroad(crossroad) {
    const sf::Color rect_color(170, 170, 170);
    const sf::Color outline_color(230, 230, 230);

    sprite = new sf::RectangleShape;
    std::pair<int, int> top_left_corner = crossroad->get_top_left_corner();
    top_left_corner.first *= VisualizerConsts::scale;
    top_left_corner.second *= VisualizerConsts::scale;
    std::pair<int, int> bott_right_corner = crossroad->get_bott_right_corner();
    bott_right_corner.first *= VisualizerConsts::scale;
    bott_right_corner.second *= VisualizerConsts::scale;
    sprite->setPosition(top_left_corner.first, top_left_corner.second);
    sprite->setSize(sf::Vector2f(bott_right_corner.first - top_left_corner.first,
                                 bott_right_corner.second - top_left_corner.second));
    sprite->setOutlineThickness((bott_right_corner.first - top_left_corner.first) * outline_cf);
    sprite->setFillColor(rect_color);
    sprite->setOutlineColor(outline_color);
}

CrossroadVisual::~CrossroadVisual() {
    delete sprite;
}

void CrossroadVisual::draw() {
    window->draw(*sprite);
}
