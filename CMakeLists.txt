cmake_minimum_required(VERSION 3.4)
project(traffic_simulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp World.cpp World.h World.cpp World.h World.cpp World.h Crossroad.cpp Crossroad.h TrafficLight.cpp TrafficLight.h Car.cpp Car.h Road.cpp Road.h Lane.cpp Lane.h Direction.h CrossRoadPath.cpp CrossRoadPath.h CarPath.cpp CarPath.h)
add_executable(traffic_simulator ${SOURCE_FILES})