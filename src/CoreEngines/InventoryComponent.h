#pragma once
#include "stdafx.h"
#include "Inventory.h"

namespace nb
{
	class InventoryComponent : public Component
	{
	public:
		InventoryComponent( Inventory::SLOT inventorySize = 0 );

		virtual void init() override;

		Inventory inventory;
	};
}
