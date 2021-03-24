#include "aircraft_manager.hpp"

#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end());
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [this](std::unique_ptr<Aircraft>& aircraft) {
        if(!aircraft->update()) {
            aircraft_factory.delete_flight_num(aircraft);
            return true;
        } 
        return false;
    }), aircrafts.end());

    return true;
}

void AircraftManager::init()
{
    aircraft_factory.init_aircraft_types();
}

std::unique_ptr<Aircraft> AircraftManager::create_aircraft(Airport* airport)
{
    return aircraft_factory.create_random_aircraft(airport);
}

int AircraftManager::nb_get_airlines(int index)
{
    const std::string air = aircraft_factory.get_airline(index);
    int number = count_if(aircrafts.begin(), aircrafts.end(),
        [air](const std::unique_ptr<Aircraft>& aircraft){ return aircraft->get_flight_num().find(air) != std::string::npos;});
    return number;
}