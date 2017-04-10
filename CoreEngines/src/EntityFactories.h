#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "NeedsComponent.h"
#include "InventoryComponent.h"

#include "ResourceEngine.h"

namespace nb
{
	Entity createHuman( const CoreEngineManager& engines,
						sf::Vector3i position = { 0,0,0 } );

	Entity createTilemapChunk( const CoreEngineManager& engines,
							   sf::Vector3i positionInChunks,
							   std::vector<std::vector<const Tile*>> tiles );

	Entity createTree( const CoreEngineManager& engines,
					   sf::Vector3i position );
}
