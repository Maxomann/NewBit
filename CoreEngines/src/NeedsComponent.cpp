#include "NeedsComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::NeedsComponent::init()
{
}

void nb::NeedsComponent::destroy()
{
}

int nb::NeedsComponent::getHunger() const
{
	return hunger;
}

void nb::NeedsComponent::setHunger( float val )
{
	hunger = val;
	if (hunger < 0)
		hunger = 0;
	if (hunger > 100)
		hunger = 100;
}

void nb::NeedsComponent::changeHunger( float change )
{
	hunger += change;
	if (hunger < 0)
		hunger = 0;
	if (hunger > 100)
		hunger = 100;
}
