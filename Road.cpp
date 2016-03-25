#include "Road.h"

Road::~Road() {
    for(auto lane : lanes)
        delete lane;
}
