#pragma once
#include "stdafx.h"
#include "WorldGenerator.h"

#include "ResourceEngine.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TileMapComponent.h"
#include "ChunkSystem.h"
#include "MathExtensions.h"
#include "PhysicsComponent.h"
#include "EntityFactories.h"

namespace nb
{
	class DefaultWorldGenerator : public WorldGenerator
	{
		noise::module::Perlin noiseGenerator;

		const ResourceEngine*const r_resourceEngine;

	public:
		DefaultWorldGenerator( const ResourceEngine*const resourceEngine );

		// thread safe
		DLL_EXPORT virtual std::vector<Entity> generateChunk( const sf::Vector3i& chunkPosition )const override;
	};
}
