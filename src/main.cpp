#include "tower_sim.hpp"

int main(int argc, char** argv)
{
    TowerSimulation simulation { argc, argv };
    Point3D p {.0, .1, .2 };
    simulation.launch();

    return 0;
}