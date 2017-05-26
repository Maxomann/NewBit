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

bool nb::Inventory::containsItem( const Item * itemPtr ) const
{
	auto it = std::find_if( items.begin(), items.end(), [&] ( const auto& el ){
		return ( el.get() == itemPtr );
	} );

	return ( it != items.end() );
}

void nb::Inventory::removeItem( const Item * itemPtr )
{
	items.erase( remove_if( items.begin(), items.end(), [&] ( const auto& el ){
		return ( el.get() == itemPtr );
	} ), items.end() );

	s_contentChange.call( *this );
}

const Inventory::ContainerType & nb::Inventory::getContent() const
{
	return items;
}
