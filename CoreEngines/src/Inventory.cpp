#include "Inventory.h"
using namespace std;
using namespace nb;

nb::Inventory::Inventory( const SLOT slotCount )
	: maxSlots( slotCount )
{
}

Inventory::COUNT nb::Inventory::addItem( const Item * item, COUNT count )
{
	auto addedCount = 0;

	auto firstSlotWithItem = getFistSlotWithItem( item );
	if (isSlotValid( firstSlotWithItem ))
	{
		itemsBySlot.at( firstSlotWithItem ).second += count;
		addedCount = count;
	}
	else
	{
		auto firstFreeSlot = getFirstFreeSlot();
		if (isSlotValid( firstFreeSlot ))
		{
			auto& foundSlot = itemsBySlot[firstFreeSlot];
			foundSlot.first = item;
			foundSlot.second += count;
			addedCount = count;
		}
	}

	if (addedCount != 0)
		s_contentChange.call( *this );

	// no slot with item & no free slot
	return addedCount;
}

Inventory::COUNT nb::Inventory::removeItem( const Item * item, COUNT count )
{
	auto removed = 0u;
	auto slotWithItem = getFistSlotWithItem( item );
	while (isSlotValid( slotWithItem ) && removed < count)
	{
		auto& foundSlot = itemsBySlot.at( slotWithItem );
		auto toRemove = count;
		if (count > foundSlot.second)
			toRemove = foundSlot.second;
		foundSlot.second -= toRemove;

		if (foundSlot.second == 0)
			itemsBySlot.erase( slotWithItem );

		slotWithItem = getFistSlotWithItem( item );
	}

	if (removed != 0)
		s_contentChange.call( *this );

	return removed;
}

const Inventory::ContainerType & nb::Inventory::getContent() const
{
	return itemsBySlot;
}

Inventory::SLOT nb::Inventory::getFirstFreeSlot() const
{
	for (SLOT i = 0; maxSlots == 0 || i < maxSlots; ++i)
	{
		auto el = itemsBySlot.find( i );
		if (el == itemsBySlot.end() || el->second.second == 0)
			if (maxSlots == 0 || i < maxSlots)
				return i;
	}

	return invalidSlot();
}

Inventory::SLOT nb::Inventory::getFistSlotWithItem( const Item * item ) const
{
	SLOT retVal = 0;

	for (const auto& el : itemsBySlot)
		if (el.second.first == item)
			return el.first;

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
