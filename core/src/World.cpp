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

World::World()
        : car_counter(0), max_route(100),
          car_velocity_min(3), car_velocity_max(13),
          car_length_min(2800), car_length_max(3600),
          car_min_gap_min(100), car_min_gap_max(200),
          car_time_headway_min(40), car_time_headway_max(60),
          car_cruise_speed_min(8.2), car_cruise_speed_max(14),
          car_max_acceleration_min(0.01), car_max_acceleration_max(0.1),
          car_max_deceleration_min(0.01), car_max_deceleration_max(0.1) {
}

World::~World() {
}

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
            beg_side = TOP;
            end_side = BOTTOM;
        }
        else {
            beg_side = BOTTOM;
            end_side = TOP;
        }
    }
    else {
        if(beg_crossroad->get_top_left_corner().first < end_crossroad->get_top_left_corner().first) {
            beg_side = LEFT;
            end_side = RIGHT;
        }
        else {
            beg_side = RIGHT;
            end_side = LEFT;
        }
    }
}

Car* World::gen_rand_car() {
    std::pair<Road*, Side> spawn = spawn_roads[rand() % spawn_roads.size()];
    Lane *lane = spawn.first->get_rand_lane(spawn.second);
    std::vector<Direction> route;
    gen_rand_route(spawn.first, spawn.second, route);
    return new Car(Utility::random(car_velocity_min, car_velocity_max, 3),
                   Utility::random(car_length_min, car_length_max, 3),
                   Utility::random(car_min_gap_min, car_min_gap_max),
                   Utility::random(car_time_headway_min, car_time_headway_max),
                   Utility::random(car_cruise_speed_min, car_cruise_speed_max, 3),
                   Utility::random(car_max_acceleration_min, car_max_acceleration_max, 3),
                   Utility::random(car_max_deceleration_min, car_max_deceleration_max, 3),
                   lane, route, car_counter++);
}

void World::gen_rand_route(const Road *road, Side side, std::vector<Direction> &route) {
    while(route.size() < max_route) {
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
        side = Utility::opposite(Utility::turn(side, dir));
    }
}

const std::vector<Car*>& World::get_cars() {
    return cars;
}

const std::vector<Crossroad *>& World::get_crossroads() {
    return crossroads;
}

const std::vector<Road *>& World::get_roads() {
    return roads;
}
