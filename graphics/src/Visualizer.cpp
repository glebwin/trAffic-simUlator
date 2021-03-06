#include <chrono>
#include "../../core/include/Car.h"
#include "../include/CarVisual.h"
#include "../include/CrossroadVisual.h"
#include "../include/RoadVisual.h"
#include "../include/Visualizer.h"
#include "../include/VisConsts.h"

Visualizer::Visualizer(World &world_)
        : world(world_) {
    window = new sf::RenderWindow(sf::VideoMode(1100, 650), "Traffic Simulator");

    VisConsts::get().scale = window->getSize().x / 100000.0;

    const std::vector<Car*> &world_cars = world.get_cars();
    cars.reserve(world_cars.size());
    for(Car *car : world_cars)
        cars.push_back(new CarVisual(*window, *car));

    const std::vector<Crossroad*> &world_crossroads = world.get_crossroads();
    crossroads.reserve(world_crossroads.size());
    for(Crossroad *crossroad : world_crossroads)
        crossroads.push_back(new CrossroadVisual(*window, *crossroad));

    const std::vector<Road*> &world_roads = world.get_roads();
    roads.reserve(world_roads.size());
    for(Road *road : world_roads)
        roads.push_back(new RoadVisual(*window, *road));
}

int Visualizer::run() {
    auto prev_time = std::chrono::high_resolution_clock::now();

    while(window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event))
            handle_event(event);

        auto time = std::chrono::high_resolution_clock::now();
        auto interval = std::chrono::duration_cast<std::chrono::milliseconds>(time - prev_time).count();
        prev_time = time;
        interval = std::min(static_cast<int>(interval), 10);

        world.on_tick(interval);

        update_cars();

        draw();
        sf::sleep(sf::milliseconds(1));
    }

    return 0;
}

void Visualizer::handle_event(sf::Event &event) {
    if(event.type == sf::Event::Closed)
        window->close();
}

void Visualizer::draw() {
    window->clear(sf::Color::White);

    for(CrossroadVisual *crossroad : crossroads)
        crossroad->draw();
    for(RoadVisual *road : roads)
        road->draw();
    for(CarVisual *car : cars)
        car->draw();

    window->display();
}

void Visualizer::update_cars() {
    const std::vector<Car*> &world_cars = world.get_cars();

    for(int i = 0; i < world_cars.size(); i++)
        if(cars[i]->get_id() != world_cars[i]->get_id()) {
            delete cars[i];
            cars[i] = new CarVisual(*window, *world_cars[i]);
        }
}
