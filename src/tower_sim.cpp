#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <utility>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    GL::move_queue.emplace(&aircraft_manager);

    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { aircraft_manager.add(aircraft_manager.create_aircraft(airport->get_tower())); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('z', []() { GL::ticks_per_sec = std::max(GL::ticks_per_sec - 1u, 1u); });
    GL::keystrokes.emplace('a', []() { GL::ticks_per_sec = std::min(GL::ticks_per_sec + 1u, 180u); });
    GL::keystrokes.emplace('p', []() { GL::is_paused = !GL::is_paused; });
    GL::keystrokes.emplace('0', [this]() { std::cout << aircraft_manager.nb_get_airlines(0) << std::endl;});
    GL::keystrokes.emplace('1', [this]() { std::cout << aircraft_manager.nb_get_airlines(1) << std::endl;});
    GL::keystrokes.emplace('2', [this]() { std::cout << aircraft_manager.nb_get_airlines(2) << std::endl;});
    GL::keystrokes.emplace('3', [this]() { std::cout << aircraft_manager.nb_get_airlines(3) << std::endl;});
    GL::keystrokes.emplace('4', [this]() { std::cout << aircraft_manager.nb_get_airlines(4) << std::endl;});
    GL::keystrokes.emplace('5', [this]() { std::cout << aircraft_manager.nb_get_airlines(5) << std::endl;});
    GL::keystrokes.emplace('6', [this]() { std::cout << aircraft_manager.nb_get_airlines(6) << std::endl;});
    GL::keystrokes.emplace('7', [this]() { std::cout << aircraft_manager.nb_get_airlines(7) << std::endl;});
    GL::keystrokes.emplace('m', [this]() { std::cout << aircraft_manager.get_number_crash() << " crash !" << std::endl; });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    std::for_each(GL::keystrokes.cbegin(), GL::keystrokes.cend(), [](std::pair<char, GL::KeyStroke> keys){std::cout << keys.first << std::endl;});
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() }, aircraft_manager };
    assert(airport != nullptr) && "airport cannot be null";
    GL::move_queue.emplace(airport);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    aircraft_manager.init();

    GL::loop();
}