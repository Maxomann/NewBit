#include "ItemComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::ItemComponent::ItemComponent( std::unique_ptr<Item> item )
	:item( move( item ) )
{}

void nb::ItemComponent::init()
{}

const std::unique_ptr<Item>& ItemComponent::getItem()const
{
	return item;
}

std::unique_ptr<Item> nb::ItemComponent::moveItem()
{
	return move( item );
}
