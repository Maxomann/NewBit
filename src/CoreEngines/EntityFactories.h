#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "NeedsComponent.h"
#include "InventoryComponent.h"

#include "EntityFactory.h"

namespace nb
{
	class ResourceEngine;
	class Tile;

	Entity createHuman( const CoreEngineManager& engines,
						sf::Vector3i position = { 0,0,0 } );

	Entity createTilemapChunk( const CoreEngineManager& engines,
							   sf::Vector3i positionInChunks,
							   std::vector<std::vector<const Tile*>> tiles );

	Entity createTree( const CoreEngineManager& engines,
					   sf::Vector3i position );

	class TreeFactory : public EntityFactory
	{
	public:
		TreeFactory();

		virtual Entity create( const ResourceEngine& resources )const override;
	};

	class ItemWoodFactory : public EntityFactory
	{
	public:
		ItemWoodFactory();

		virtual Entity create( const ResourceEngine& resources )const override;
	};

	class WallFactory : public EntityFactory
	{
	public:
		WallFactory();

		virtual Entity create( const ResourceEngine& resources )const override;
	};
}
