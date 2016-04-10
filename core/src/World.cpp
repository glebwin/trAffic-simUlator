#include <fstream>
#include <unordered_map>
#include <sstream>
#include "../include/Car.h"
#include "../include/Crossroad.h"
#include "../include/Road.h"
#include "../include/TrafficLight.h"
#include "../include/World.h"

void World::on_tick(unsigned int delta_ms) {
    for(auto it : cars)
        it->on_tick(delta_ms);
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

            add_road(new Road(beg_crossroad, beg_side, end_crossroad, end_side,
                              forward_lanes_num, backward_lanes_num));
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
