#pragma once
#include "stdafx.h"
#include "TextureManager.h"
#include "Item.h"

#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ItemComponent.h"

namespace nb
{
	class ItemManager
	{
		std::list<Item> items;

		void parseFile( const std::string& path,
						const TextureManager& textures );

	public:
		void init( const PackageManager& packages,
				   const TextureManager& textures );

		// The returned value is thread safe
		// It will not be modified after init() has been called
		const Item* getItem( Item::ID id )const;

		const std::list<Item>& getAllItems()const;

		static Entity createItemEntity( const Item* item,
										sf::Vector3i position );
	};
}
