#include "Inventory.h"
using namespace std;
using namespace nb;

nb::Inventory::Inventory( const SLOT slotCount )
	: maxSlots( slotCount )
{
}

Inventory::COUNT nb::Inventory::addItem( Item * item, COUNT count )
{
	auto firstSlotWith = getFistSlotWithItem( item );
	if (firstSlotWith != invalidSlot())
	{
		itemsBySlot.at( firstSlotWith ).second += 1;
	}
	else
	{
		auto firstFreeSlot = getFirstFreeSlot();
		if (firstFreeSlot != invalidSlot())
		{
			auto& slotToUse = itemsBySlot[firstFreeSlot];
			slotToUse.first = item;
			slotToUse.second = 1;
		}
	}

	return COUNT();
}

Inventory::COUNT nb::Inventory::addItemToSlot( Item * item, SLOT slot, COUNT count )
{
	if (isSlotValid( slot ))
	{
		auto& slotToUse = itemsBySlot[slot];
	}

	return COUNT();
}

Inventory::COUNT nb::Inventory::removeItem( Item * item, COUNT count )
{
	return COUNT();
}

Inventory::COUNT nb::Inventory::removeItemFromSlot( Item * item, SLOT slot, COUNT count )
{
	return COUNT();
}

const Inventory::ContainerType & nb::Inventory::getContent() const
{
	return itemsBySlot;
}

Inventory::SLOT nb::Inventory::getFirstFreeSlot() const
{
	SLOT retVal = 0;

	for (const auto& el : itemsBySlot)
	{
		if (el.first == retVal + 1)
			retVal = el.first;
		else
		{
			retVal++;
			break;
		}
	}

	if (retVal >= invalidSlot())
		return invalidSlot();
	else
		return retVal;
}

Inventory::SLOT nb::Inventory::getFistSlotWithItem( Item * item ) const
{
	auto found = find_if( itemsBySlot.begin(), itemsBySlot.end(), [&]( const ContainerType::value_type& el ) {
		return el.second.first == item;
	} );

	if (found != itemsBySlot.end())
	{
		return found->first;
	}
	else
	{
		return invalidSlot();
	}
}

bool nb::Inventory::isSlotValid( SLOT slot ) const
{
	return (slot < invalidSlot());
}

Inventory::SLOT nb::Inventory::invalidSlot() const
{
	if (maxSlots != 0)
		return maxSlots;
	else
		return std::numeric_limits<SLOT>::max();
}
