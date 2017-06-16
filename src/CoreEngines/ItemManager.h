#pragma once
#include "stdafx.h"
#include "TextureManager.h"
#include "Item.h"

#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "ItemComponent.h"

#include "SpriteRenderer.h"

#include "LabeledFactoryManager.h"
#include "ItemFactory.h"

#include "DefaultItemFactory.h"
#include "DefaultFoodItemFactory.h"

namespace nb
{
	class ItemManager : public LabeledFactoryManager< ItemFactory >
	{
		void parseObject( const TextureManager& textures,
						  const nlohmann::json& el );

		void parseFile( const std::string& path,
						const TextureManager& textures );

	public:
		void init( const PackageManager& packages,
				   const TextureManager& textures );

		static Entity createItemEntity( std::unique_ptr<Item> item,
										sf::Vector3i position );
		static Entity createItemEntity( std::unique_ptr<Item> item,
										Position position );
	};
}
