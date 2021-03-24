#pragma once

#include <vector>

#include "aircraft_types.hpp"
#include "airport.hpp"

class Aircraft;

class AircraftFactory
{
private:
    const int min_fuel = 300;
    const int max_fuel = 3000;
    
    const static size_t NUM_AIRCRAFT_TYPES = 3;
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    std::vector<std::string> flight_num;

    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport);

public:
    void init_aircraft_types();

    [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);

    std::string get_airline(int);

    void delete_flight_num(std::unique_ptr<Aircraft>&);
};
