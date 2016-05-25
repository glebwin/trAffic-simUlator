#include "../../core/include/Car.h"
#include "../../core/include/Lane.h"
#include "../include/CarVisual.h"
#include "../include/VisConsts.h"

CarVisual::CarVisual(sf::RenderWindow &window, const Car &car)
        : window(window), car(car) {
    id = car.get_id();

    sprite.setOrigin(car.get_length(), VisConsts::get().car_width / 2);
    sprite.setSize(sf::Vector2f(car.get_length(), VisConsts::get().car_width));
    sprite.setScale(VisConsts::get().scale, VisConsts::get().scale);
    sprite.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

void CarVisual::draw() {
    calc_pos();
    window.draw(sprite);
}

int CarVisual::get_id() {
    return id;
}

void CarVisual::calc_pos() {
    Lane *lane = car.get_lane();
    std::pair<int, int> beg_coord = lane->get_beg();
    int pos = car.get_lane_coord();
    const int quart_ang = 90;

    switch(lane->get_beg_side()) {
        case TOP:
            sprite.setRotation(quart_ang);
            sprite.setPosition(beg_coord.first, beg_coord.second + pos);
            break;
        case RIGHT:
            sprite.setRotation(0);
            sprite.setPosition(beg_coord.first - pos, beg_coord.second);
            break;
        case BOTTOM:
            sprite.setRotation(quart_ang * 3);
            sprite.setPosition(beg_coord.first, beg_coord.second - pos);
            break;
        case LEFT:
            sprite.setRotation(quart_ang * 2);
            sprite.setPosition(beg_coord.first + pos, beg_coord.second);
            break;
    }
    sprite.setPosition(sprite.getPosition().x * VisConsts::get().scale,
                       sprite.getPosition().y * VisConsts::get().scale);
}
