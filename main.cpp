#include "graphics/include/Visualizer.h"

int main() {
    World *world = new World();
    world->read_file("input.txt");
    Visualizer *visualizer = new Visualizer(*world);
    visualizer->run();
    return 0;
}
