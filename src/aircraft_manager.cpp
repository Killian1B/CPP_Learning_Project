#include "aircraft_manager.hpp"

#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    for (auto aircraft_it = aircrafts.begin(); aircraft_it != aircrafts.end();)
    {
        auto& aircraft = **aircraft_it;
        if (aircraft.update())
        {
            ++aircraft_it;
        }
        else
        {
            aircraft_it = aircrafts.erase(aircraft_it);
        }
    }

    return true;
}

void AircraftManager::init()
{
    aircraft_factory.init_aircraft_types();
}

std::unique_ptr<Aircraft> AircraftManager::create_aircraft(Airport* airport) const
{
    return aircraft_factory.create_random_aircraft(airport);
}