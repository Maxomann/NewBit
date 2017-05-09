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
		auto change = -1 * 0.0002f * timeSystem->getTimestep().asMilliseconds();

		el->changeHunger( change );
	}
}

void nb::NeedsSystem::destroy()
{}
