#include "NeedsSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::NeedsSystem::init()
{
	timeSystem = system<TimeSystem>();

	needsComponentCache.connectToWorld( world() );
}

void nb::NeedsSystem::update()
{
	for( auto& el : needsComponentCache.get() )
	{
		const auto& timestep = timeSystem->getTimestep();

		el->changeValuesOverTime( timestep );
	}
}

void nb::NeedsSystem::destroy()
{}
