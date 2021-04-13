#pragma once

#include <vector>

#include "aircraft_types.hpp"
#include "tower.hpp"
#include "aircraft.hpp"

class AircraftFactory
{
private:    
    const static size_t NUM_AIRCRAFT_TYPES = 3;
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    std::vector<std::string> flight_num;

    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Tower& tower);

public:
    void init_aircraft_types();

    [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft(Tower& tower);

    std::string get_airline(int);

    void delete_flight_num(std::unique_ptr<Aircraft>&);
};
