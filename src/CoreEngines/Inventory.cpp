#include "Inventory.h"
using namespace std;
using namespace nb;

void nb::Inventory::addItem( std::unique_ptr<Item> item )
{
	items.push_back( move( item ) );
}

const Inventory::ContainerType & nb::Inventory::getContent() const
{
	return items;
}
