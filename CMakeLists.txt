cmake_minimum_required(VERSION 3.4)
project(traffic_simulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp core/src/World.cpp core/include/World.h core/src/World.cpp core/include/World.h core/src/World.cpp core/include/World.h core/src/Crossroad.cpp core/include/Crossroad.h core/src/TrafficLight.cpp core/include/TrafficLight.h core/src/Car.cpp core/include/Car.h core/src/Road.cpp core/include/Road.h core/src/Lane.cpp core/include/Lane.h core/include/Side.h core/include/Direction.h core/include/Utility.h core/src/Utility.cpp graphics/src/Visualizer.cpp graphics/include/Visualizer.h)
add_executable(traffic_simulator ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(traffic_simulator ${SFML_LIBRARIES})
endif()