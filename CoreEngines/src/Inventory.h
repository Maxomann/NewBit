#pragma once
#include "stdafx.h"
#include "Item.h"

namespace nb
{
	class Inventory
	{
	public:
		using SLOT = unsigned int;
		using COUNT = unsigned int;

		// map< SLOT pair< ITEM, COUNT > >
		using ContainerType = std::map<SLOT, std::pair<Item*, COUNT>>;

	private:
		ContainerType itemsBySlot;

		SLOT maxSlots;

	public:
		Inventory( const SLOT slotCount = 0 );

		COUNT addItem( Item* item, COUNT count = 1 );
		COUNT addItemToSlot( Item* item, SLOT slot, COUNT count = 1 );

		COUNT removeItem( Item* item, COUNT count = 1 );
		COUNT removeItemFromSlot( Item* item, SLOT slot, COUNT count = 1 );

		SLOT getFirstFreeSlot()const;
		SLOT getFistSlotWithItem( Item* item )const;

		bool isSlotValid( SLOT slot )const;
		SLOT invalidSlot()const;

		const ContainerType& getContent()const;
	};
}
