#include "NeedsComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::NeedsComponent::NeedsComponent()
	:hunger( 100 )
{
}

void nb::NeedsComponent::init()
{
}

void nb::NeedsComponent::destroy()
{
}

float nb::NeedsComponent::getHunger() const
{
	return hunger;
}

void nb::NeedsComponent::setHunger( float val )
{
	auto oldHunger = hunger;
	hunger = val;

	if (hunger < 0)
		hunger = 0;
	if (hunger > 100)
		hunger = 100;

	s_hungerChanged.call( this, oldHunger );
}

void nb::NeedsComponent::changeHunger( float change )
{
	setHunger( hunger + change );
}
