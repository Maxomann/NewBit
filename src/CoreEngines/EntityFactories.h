#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "NeedsComponent.h"
#include "InventoryComponent.h"
#include "ItemSpawnerComponent.h"

#include "EntityFactory.h"

namespace nb
{
	class ResourceEngine;
	class Tile;
	class TextureManager;
	class TextureReference;
	class ItemManager;

	Entity createHuman( const ResourceEngine*const resources,
						sf::Vector3i position = {0,0,0} );

	Entity createTilemapChunk( const ResourceEngine*const resources,
							   sf::Vector3i positionInChunks,
							   std::vector<std::vector<const Tile*>> tiles );

	class TreeFactory : public EntityFactory
	{
		const TextureReference* texref;
		const ItemFactory* appleItemFactory;
		const ItemFactory* woodItemFactory;

		ItemSpawnTask appleSpawnTask;
		ItemSpawnTask woodSpawnTask;

	public:
		TreeFactory( const TextureManager& textures,
					 const ItemManager& items );

		virtual Entity create()const override;
	};

	class WallFactory : public EntityFactory
	{
		const TextureReference* texref;

	public:
		WallFactory( const TextureManager& textures );

		virtual Entity create()const override;
	};
}
