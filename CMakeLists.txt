cmake_minimum_required(VERSION 3.4)
project(traffic_simulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp core/src/World.cpp core/include/World.h core/src/World.cpp core/include/World.h core/src/World.cpp core/include/World.h core/src/Crossroad.cpp core/include/Crossroad.h core/src/TrafficLight.cpp core/include/TrafficLight.h core/src/Car.cpp core/include/Car.h core/src/Road.cpp core/include/Road.h core/src/Lane.cpp core/include/Lane.h core/src/CrossroadPath.cpp core/include/CrossroadPath.h core/src/CarPath.cpp core/include/CarPath.h core/include/Side.h)
add_executable(traffic_simulator ${SOURCE_FILES})