#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft_factory.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    AircraftFactory aircraft_factory;
    int number_crash = 0;

public:
    void add(std::unique_ptr<Aircraft>);

    bool update() override;

    void init();

    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(Tower&);

    int nb_get_airlines(int);

    int get_required_fuel();

    int get_number_crash();

    friend class Airport;
};