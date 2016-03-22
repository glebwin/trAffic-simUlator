#ifndef TRAFFIC_SIMULATOR_PATH_H
#define TRAFFIC_SIMULATOR_PATH_H


class Car;

class Path {
private:

    int length;

public:

    virtual Path* get_next_path() = 0;
    virtual bool can_enter_road_node() = 0;
    virtual int get_length() = 0;
};


#endif
