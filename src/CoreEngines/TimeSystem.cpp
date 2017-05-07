#include "TimeSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::TimeSystem::init()
{
	frameTime = sf::milliseconds( 8 );
}

void nb::TimeSystem::( )
{
	frameTime = clock.restart();
	if( isFirstIteartion )
	{
		frameTime = sf::milliseconds( 8 );
		isFirstIteartion = false;
	}
}

void nb::TimeSystem::destroy()
{}

const sf::Time & nb::TimeSystem::getFrameTime() const
{
	return frameTime;
}
