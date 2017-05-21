#include "Inventory.h"
using namespace std;
using namespace nb;

void nb::Inventory::addItem( std::unique_ptr<Item> item )
{
	if( item )
	{
		items.push_back( move( item ) );
		s_contentChange.call( *this );
	}
}

std::unique_ptr<Item> nb::Inventory::moveItem( size_t id )
{
	auto retVal = move( items.at( id ) );

	items.erase( items.begin() + id );
	s_contentChange.call( *this );

	return retVal;
}

const Inventory::ContainerType & nb::Inventory::getContent() const
{
	return items;
}
