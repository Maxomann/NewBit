#pragma once
#include "stdafx.h"
#include "Item.h"
#include "NeedsComponent.h"
#include "InventoryComponent.h"

namespace nb
{
	class DefaultFoodItem : public Item
	{
		const float hungerPerUse;
		const float thirstPerUse;
		const float energyPerUse;

		int usesLeft;

	public:
		DefaultFoodItem( const std::string name,
						 const TextureReference* texture,
						 const float hungerPerUse,
						 const float thirstPerUse,
						 const float energyPerUse,
						 const unsigned int uses = 1 );

		virtual void use( World& world,
						  Entity* entity )override;
	};
}
