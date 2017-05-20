#pragma once
#include "stdafx.h"

#include "InventoryComponent.h"
#include "PhysicsComponent.h"
#include "ItemComponent.h"

namespace nb
{
	class ItemPickupComponent : public Component
	{
		InventoryComponent* inventoryComponent;
		PhysicsComponent* physicsComponent;

	public:
		virtual void init() override;
	};
}
