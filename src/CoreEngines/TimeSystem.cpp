#include "TimeSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::TimeSystem::init()
{}

void nb::TimeSystem::update()
{}

void nb::TimeSystem::destroy()
{}

void nb::TimeSystem::updateTimestep( const sf::Time & step )
{
	timestep = step;
}

const sf::Time & nb::TimeSystem::getTimestep() const
{
	return timestep;
}
