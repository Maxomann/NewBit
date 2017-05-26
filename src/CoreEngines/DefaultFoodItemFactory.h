#pragma once
#include "stdafx.h"
#include "ItemFactory.h"
#include "DefaultFoodItem.h"

namespace nb
{
	class DefaultFoodItemFactory : public ItemFactory
	{
		const TextureReference* texture;

		const float hungerPerUse;
		const float thirstPerUse;
		const float energyPerUse;

		const int uses;

	public:
		DefaultFoodItemFactory( ID id,
								NAME name,
								LABELS labels,
								const TextureReference* texture,
								const float hungerPerUse,
								const float thirstPerUse,
								const float energyPerUse,
								const unsigned int uses );

		virtual std::unique_ptr<Item> create()const override;
	};
}
