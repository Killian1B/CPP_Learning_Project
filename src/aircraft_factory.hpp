#pragma once

#include "aircraft_types.hpp"
#include "airport.hpp"

class Aircraft;

class AircraftFactory
{
private:
    const static size_t NUM_AIRCRAFT_TYPES = 3;
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport) const;

public:
    void init_aircraft_types();

    [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport) const;
};
