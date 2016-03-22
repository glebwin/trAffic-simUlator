#ifndef TRAFFIC_SIMULATOR_TRAFFICLIGHT_H
#define TRAFFIC_SIMULATOR_TRAFFICLIGHT_H


#include <utility>
#include <vector>

class TrafficLight {

    struct CrossRoadPath {
        static const int TL = 1 << 0;
        static const int TF = 1 << 1;
        static const int TR = 1 << 2;

        static const int RL = 1 << 3;
        static const int RF = 1 << 4;
        static const int RR = 1 << 5;

        static const int BL = 1 << 6;
        static const int BF = 1 << 7;
        static const int BR = 1 << 8;

        static const int LL = 1 << 9;
        static const int LF = 1 << 10;
        static const int LR = 1 << 11;
    };

private:

    std::vector<std::pair<int, int>> schedule;

public:

    void on_tick(unsigned int delta_ms);
};


#endif
