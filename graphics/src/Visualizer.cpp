#include <chrono>
#include "../../core/include/Car.h"
#include "../include/CarVisual.h"
#include "../include/CrossroadVisual.h"
#include "../include/RoadVisual.h"
#include "../include/Visualizer.h"
#include "../include/VisConsts.h"

Visualizer::Visualizer(World *world)
        : world(world) {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Traffic Simulator");

    VisConsts::get().scale = window->getSize().x / 40000.0;

    const std::vector<Car*> &world_cars = world->get_cars();
    cars.reserve(world_cars.size());
    for(Car *car : world_cars)
        cars.push_back(new CarVisual(window, *car));

    const std::vector<Crossroad*> &world_crossroads = world->get_crossroads();
    crossroads.reserve(world_crossroads.size());
    for(Crossroad *crossroad : world_crossroads)
        crossroads.push_back(new CrossroadVisual(window, crossroad));

    const std::vector<Road*> &world_roads = world->get_roads();
    roads.reserve(world_roads.size());
    for(Road *road : world_roads)
        roads.push_back(new RoadVisual(window, road));
}

int Visualizer::run() {
    std::chrono::high_resolution_clock clock;
    auto prev_time = clock.now();

    while(window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event))
            handle_event(event);

        auto time = clock.now();
        unsigned int interval = std::chrono::duration_cast<std::chrono::milliseconds>(prev_time - time).count();
        prev_time = time;
        world->on_tick(interval);

        update_cars();

        draw();
        sf::sleep(sf::milliseconds(3));
    }

    return 0;
}

void Visualizer::handle_event(sf::Event &event) {
    if(event.type == sf::Event::Closed)
        window->close();
}

void Visualizer::draw() {
    window->clear(sf::Color::White);

    for(CarVisual *car : cars)
        car->draw();
    for(CrossroadVisual *crossroad : crossroads)
        crossroad->draw();
    for(RoadVisual *road : roads)
        road->draw();

    window->display();
}

void Visualizer::update_cars() {
    const std::vector<Car*> &world_cars = world->get_cars();

    for(int i = 0; i < world_cars.size(); i++)
        if(cars[i]->get_id() != world_cars[i]->get_id()) {
            delete cars[i];
            cars[i] = new CarVisual(window, *world_cars[i]);
        }
}
