#include "Inventory.h"
using namespace std;
using namespace nb;

nb::Inventory::Inventory( const SLOT slotCount )
	: maxSlots( slotCount )
{
}

Inventory::COUNT nb::Inventory::addItem( Item * item, COUNT count )
{
	auto firstSlotWithItem = getFistSlotWithItem( item );
	if (isSlotValid( firstSlotWithItem ))
	{
		itemsBySlot.at( firstSlotWithItem ).second += count;
		return count;
	}
	else
	{
		auto firstFreeSlot = getFirstFreeSlot();
		if (isSlotValid( firstFreeSlot ))
		{
			auto& foundSlot = itemsBySlot.at( firstFreeSlot );
			foundSlot.first = item;
			foundSlot.second += count;
			return count;
		}
	}

	// no slot with item & no free slot
	return COUNT( 0 );
}

Inventory::COUNT nb::Inventory::removeItem( Item * item, COUNT count )
{
	auto removed = 0;
	auto slotWithItem = getFistSlotWithItem( item );
	while (isSlotValid( slotWithItem ) && removed < count)
	{
		auto& foundSlot = itemsBySlot.at( slotWithItem );
		auto toRemove = count;
		if (count > foundSlot.second)
			toRemove = foundSlot.second;
		foundSlot.second -= toRemove;

		if (foundSlot.second == 0)
			foundSlot.first == nullptr;

		slotWithItem = getFistSlotWithItem( item );
	}

	return removed;
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
		if (el.second == 0)
			return retVal;
		else
			retVal++;
	}

	return invalidSlot();
}

Inventory::SLOT nb::Inventory::getFistSlotWithItem( Item * item ) const
{
	SLOT retVal = 0;

	for (const auto& el : itemsBySlot)
	{
		if (el.first == item)
			return retVal;
		else
			retVal++;
	}

	return invalidSlot();
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
