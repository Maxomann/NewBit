#include "NeedsComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::NeedsComponent::NeedsComponent()
{}

void nb::NeedsComponent::init()
{}

void nb::NeedsComponent::changeValuesOverTime( const sf::Time & time )
{
	auto asMilliseconds = time.asMilliseconds();

	changeHunger( -1 * baseHungerRate * asMilliseconds );
	changeThirst( -1 * baseThirstRate * asMilliseconds );
	changeEnergy( -1 * baseEnergyRate * asMilliseconds );
}

float nb::NeedsComponent::getHunger() const
{
	return hunger;
}

void nb::NeedsComponent::setHunger( float val )
{
	auto oldHunger = hunger;
	hunger = val;

	if( hunger < 0 )
		hunger = 0;
	if( hunger > 100 )
		hunger = 100;

	s_hungerChanged.call( this, oldHunger );
}

void nb::NeedsComponent::changeHunger( float change )
{
	setHunger( hunger + change );
}

float nb::NeedsComponent::getThirst() const
{
	return thirst;
}

void nb::NeedsComponent::setThirst( float val )
{
	auto oldHunger = thirst;
	thirst = val;

	if( thirst < 0 )
		thirst = 0;
	if( thirst > 100 )
		thirst = 100;

	s_thirstChanged.call( this, oldHunger );
}

void nb::NeedsComponent::changeThirst( float change )
{
	setThirst( thirst + change );
}

float nb::NeedsComponent::getEnergy() const
{
	return energy;
}

void nb::NeedsComponent::setEnergy( float val )
{
	auto oldHunger = energy;
	energy = val;

	if( energy < 0 )
		energy = 0;
	if( energy > 100 )
		energy = 100;

	s_energyChanged.call( this, oldHunger );
}

void nb::NeedsComponent::changeEnergy( float change )
{
	setEnergy( energy + change );
}
