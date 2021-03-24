#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"
#include "aircraft_factory.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    AircraftFactory aircraft_factory;

public:
    void add(std::unique_ptr<Aircraft>);

    bool update() override;

    void init();

    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(Airport*);

    int nb_get_airlines(int);
};