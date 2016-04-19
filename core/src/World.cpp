#include <cstdlib>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include "../include/Car.h"
#include "../include/Crossroad.h"
#include "../include/Road.h"
#include "../include/TrafficLight.h"
#include "../include/Utility.h"
#include "../include/World.h"

void World::on_tick(unsigned int delta_ms) {
    for(auto it : cars) {
        if(it->drove_away()) {
            delete it;
            it = gen_rand_car();
        }
        it->on_tick(delta_ms);
    }
    for(auto it : crossroads)
        it->on_tick(delta_ms);
}

void World::add_car(Car *car) {
    cars.push_back(car);
}

void World::add_crossroad(Crossroad *crossroad) {
    crossroads.push_back(crossroad);
}

void World::add_road(Road *road) {
    roads.push_back(road);
}

void World::add_spawn(Road *road, Side side) {
    spawn_roads.push_back(std::make_pair(road, side));
}

void World::read_file(std::string file_name) {
    std::ifstream file_in(file_name);

    std::unordered_map<std::string, Crossroad*> crossroads;
    Crossroad *prev_crossroad;

    for(std::string line; std::getline(file_in, line);) {
        std::istringstream stream(line);

        std::string type;
        stream >> type;

        if(type == "crossroad") {
            std::string id;
            std::pair<int, int> top_left_corner;
            std::pair<int, int> bott_right_corner;
            stream >> id
                   >> top_left_corner.first >> top_left_corner.second
                   >> bott_right_corner.first >> bott_right_corner.second;

            Crossroad *crossroad = new Crossroad(top_left_corner, bott_right_corner);
            crossroads[id] = crossroad;
            prev_crossroad = crossroad;
            add_crossroad(crossroad);
        }
        else if(type == "traffic_light") {
            std::vector<TrafficLight::ScheduleUnit> schedule;
            int mask;
            unsigned int duration;
            while(stream >> mask >> duration) {
                schedule.push_back(TrafficLight::ScheduleUnit(mask, duration));
            }
            prev_crossroad->set_traffic_light(new TrafficLight(schedule));
        }
        else if(type == "road") {
            std::string crossroad1_id;
            std::string crossroad2_id;
            unsigned int forward_lanes_num;
            unsigned int backward_lanes_num;
            stream >> crossroad1_id >> crossroad2_id
                   >> forward_lanes_num >> backward_lanes_num;

            Crossroad *beg_crossroad = crossroads[crossroad1_id];
            Crossroad *end_crossroad = crossroads[crossroad2_id];
            Side beg_side;
            Side end_side;
            get_road_sides(beg_crossroad, end_crossroad, beg_side, end_side);

            Road *road = new Road(beg_crossroad, beg_side, end_crossroad, end_side,
                                  forward_lanes_num, backward_lanes_num);
            add_road(road);
            add_spawn(road, road->get_beg_side());
            add_spawn(road, road->get_end_side());
        }
        else if(type == "cars") {
            unsigned int number;
            stream >> number;
            cars.reserve(number);
            for(unsigned int i = 0; i < number; i++)
                cars.push_back(gen_rand_car());
        }
    }
}

void World::get_road_sides(Crossroad *beg_crossroad, Crossroad *end_crossroad, Side &beg_side, Side &end_side) {
    if(beg_crossroad->get_top_left_corner().first == end_crossroad->get_top_left_corner().first) {
        if(beg_crossroad->get_top_left_corner().second < end_crossroad->get_top_left_corner().second) {
            beg_side = RIGHT;
            end_side = LEFT;
        }
        else {
            beg_side = LEFT;
            end_side = RIGHT;
        }
    }
    else {
        if(beg_crossroad->get_top_left_corner().first < end_crossroad->get_top_left_corner().first) {
            beg_side = BOTTOM;
            end_side = TOP;
        }
        else {
            beg_side = TOP;
            end_side = BOTTOM;
        }
    }
}

Car* World::gen_rand_car() {
    std::pair<Road*, Side> spawn = spawn_roads[rand() % spawn_roads.size()];
    Lane *lane = spawn.first->get_rand_lane(spawn.second);
    std::vector<Direction> route;
    gen_rand_route(spawn.first, spawn.second, route);
    return new Car(rand() % 750000 + 250000, rand() % 1000 + 2500, rand() % 500 + 500,
                   rand() % 2000 + 500, rand() % 6000000 + 8000000, rand(), rand(), lane, route);
}

void World::gen_rand_route(Road *road, Side side, std::vector<Direction> &route) {
    while(1) {
        side = Utility::opposite(side);
        Crossroad *crossroad = road->get_next_crossroad(side);
        Direction dir = static_cast<Direction>(rand() % DIRECTIONS_NUM);
        Road *next_road = crossroad->get_road(Utility::turn(side, dir));
        if(!next_road) {
            dir = static_cast<Direction>(rand() % DIRECTIONS_NUM);
            next_road = crossroad->get_road(Utility::turn(side, dir));
            if(!next_road)
                break;
        }
        route.push_back(dir);
        road = next_road;
        side = Utility::turn(side, dir);
    }
}
