#include "../../core/include/Car.h"
#include "../../core/include/Lane.h"
#include "../include/CarVisual.h"
#include "../include/VisConsts.h"

CarVisual::CarVisual(sf::RenderWindow *window, const Car &car)
        : window(window), car(car) {
    id = car.get_id();

    sprite.setOrigin(car.get_length(), VisConsts::get().car_width / 2);
    sprite.setScale(VisConsts::get().scale, VisConsts::get().scale);
    sprite.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

void CarVisual::draw() {
    calc_coord();
    window->draw(sprite);
}

int CarVisual::get_id() {
    return id;
}

void CarVisual::calc_coord() {
    std::pair<int, int> beg_coord = car.get_lane()->get_beg();
    std::pair<int, int> end_coord = car.get_lane()->get_end();
    if(car.get_lane()->is_hor()) {

    }
}
