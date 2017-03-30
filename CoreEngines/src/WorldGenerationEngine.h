#pragma once
#include "stdafx.h"
#include "ResourceEngine.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TerrainComponent.h"
#include "ChunkSystem.h"
#include "MathExtensions.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

namespace nb
{
	class WorldGenerationEngine : public CoreEngine
	{
		std::random_device rd;
		std::mt19937 mt;
		std::uniform_int_distribution<int> dist;
		std::uniform_int_distribution<int> dist2;
		noise::module::Perlin noiseGenerator;

		const CoreRef* r_core;
		ResourceEngine* r_resourceEngine;

	public:
		DLL_EXPORT WorldGenerationEngine();

		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual bool update()override;

		// thread safe
		DLL_EXPORT std::vector<Entity> generateChunk( const sf::Vector3i& chunkPosition );
	};
}
