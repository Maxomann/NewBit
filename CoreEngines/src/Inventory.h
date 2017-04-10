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
		using ContainerType = std::vector<std::pair<Item*, COUNT>>;

	private:
		ContainerType itemsBySlot;

		SLOT maxSlots;

		SLOT invalidSlot()const;
	public:
		Inventory( const SLOT slotCount = 0 );

		COUNT addItem( Item* item, COUNT count = 1 );

		COUNT removeItem( Item* item, COUNT count = 1 );

		SLOT getFirstFreeSlot()const;
		SLOT getFistSlotWithItem( Item* item )const;

		bool isSlotValid( SLOT slot )const;

		const ContainerType& getContent()const;
	};
}
