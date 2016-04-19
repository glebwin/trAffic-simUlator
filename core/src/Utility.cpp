#include "../include/Utility.h"

Side Utility::turn(Side turn_side, Direction turn_dir) {
    return static_cast<Side>((turn_side + turn_dir - 1 + SIDES_NUM) % SIDES_NUM);
}

Side Utility::opposite(Side side) {
    return static_cast<Side>(side ^ 1);
}
