#include "aircraft_factory.hpp"

void AircraftFactory::init_aircraft_types()
{
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .02f, .08f, .02f, MediaPath { "concorde_af.png" } };
}

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type, Tower& tower)
{
    std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    while(std::find(flight_num.begin(), flight_num.end(), flight_number) != flight_num.end())
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    flight_num.emplace(flight_number);
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    return std::make_unique<Aircraft> ( type, flight_number, start, direction, tower );
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Tower& tower)
{
    return create_aircraft(*(aircraft_types[rand() % 3]), tower);
}

std::string AircraftFactory::get_airline(int index)
{
    return airlines[index];
}

void AircraftFactory::delete_flight_num(std::unique_ptr<Aircraft>& aircraft)
{
    auto it = std::find(flight_num.begin(), flight_num.end(), aircraft->get_flight_num());
    if(it != flight_num.end())
    {
        flight_num.erase(it);
    }
}