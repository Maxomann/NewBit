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
		using ContainerType = std::map<SLOT, std::pair<const Item*, COUNT>>;

	private:
		ContainerType itemsBySlot;

		SLOT maxSlots;

		SLOT invalidSlot()const;
	public:
		Inventory( const SLOT slotCount = 0 );

		COUNT addItem( const Item* item, COUNT count = 1 );

		COUNT removeItem( const Item* item, COUNT count = 1 );

		SLOT getFirstFreeSlot()const;
		SLOT getFistSlotWithItem( const Item* item )const;

		bool isSlotValid( SLOT slot )const;

		const ContainerType& getContent()const;

		Signal<void( const Inventory& )> s_contentChange;
	};
}
