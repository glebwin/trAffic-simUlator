#include "../../core/include/Crossroad.h"
#include "../include/CrossroadVisual.h"
#include "../include/VisConsts.h"

CrossroadVisual::CrossroadVisual(sf::RenderWindow &window, const Crossroad &crossroad)
        : window(window), crossroad(crossroad) {
    std::pair<int, int> top_left_corner = crossroad.get_tl_corner();
    std::pair<int, int> bott_right_corner = crossroad.get_br_corner();
    sprite.setPosition(top_left_corner.first, top_left_corner.second);
    sprite.setSize(sf::Vector2f(bott_right_corner.first - top_left_corner.first,
                                 bott_right_corner.second - top_left_corner.second));
    sprite.setOutlineThickness(VisConsts::get().road_outline_thickness);
    sprite.setFillColor(VisConsts::get().asphalt_col);
    sprite.setOutlineColor(VisConsts::get().road_outline_col);

    sprite.setPosition(sf::Vector2f(sprite.getPosition().x * VisConsts::get().scale,
                                    sprite.getPosition().y * VisConsts::get().scale));
    sprite.setScale(VisConsts::get().scale, VisConsts::get().scale);
}

CrossroadVisual::~CrossroadVisual() {
}

void CrossroadVisual::draw() {
    window.draw(sprite);
}
