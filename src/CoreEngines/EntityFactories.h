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

	Entity createHuman( const ResourceEngine*const resources,
						sf::Vector3i position = {0,0,0} );

	Entity createTilemapChunk( const ResourceEngine*const resources,
							   sf::Vector3i positionInChunks,
							   std::vector<std::vector<const Tile*>> tiles );

	Entity createTree( const ResourceEngine*const resources,
					   sf::Vector3i position );

	class TreeFactory : public EntityFactory
	{
	public:
		TreeFactory();

		virtual Entity create( const ResourceEngine& resources )const override;
	};

	class ItemEntityWoodFactory : public EntityFactory
	{
	public:
		ItemEntityWoodFactory();

		virtual Entity create( const ResourceEngine& resources )const override;
	};

	class WallFactory : public EntityFactory
	{
	public:
		WallFactory();

		virtual Entity create( const ResourceEngine& resources )const override;
	};
}
