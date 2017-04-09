#include "ItemComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::ItemComponent::ItemComponent( const Item * item )
	:item( item )
{
}

void nb::ItemComponent::init()
{
}

void nb::ItemComponent::destroy()
{
}

const Item* ItemComponent::getItem()const
{
	return item;
}
