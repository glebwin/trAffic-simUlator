#include <cmath>
#include <cstdlib>
#include "../include/Utility.h"

Side Utility::turn(Side turn_side, Direction turn_dir) {
    return static_cast<Side>((turn_side + turn_dir - 1 + SIDES_NUM) % SIDES_NUM);
}

Side Utility::opposite(Side side) {
    return static_cast<Side>(side ^ 2);
}

int Utility::random(int a, int b) {
    return rand() % (b - a + 1) + a;
}

double Utility::random(double a, double b, int prec) {
    double m = std::pow(10, prec);
    return random(a * m, b * m) / m;
}
