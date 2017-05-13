#pragma once
#include "stdafx.h"
#include "Inventory.h"

namespace nb
{
	class InventoryComponent : public Component
	{
	public:
		virtual void init() override;

		Inventory inventory;
	};
}
