#pragma once
#include "stdafx.h"
#include "ResourceEngine.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TileMapComponent.h"
#include "ChunkSystem.h"
#include "MathExtensions.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "EntityFactories.h"

namespace nb
{
	class WorldGenerationEngine : public CoreEngine
	{
		std::random_device rd;
		std::mt19937 mt;
		std::uniform_int_distribution<int> dist;
		std::uniform_int_distribution<int> dist2;

		noise::module::Const con;
		noise::module::Perlin noiseGenerator;
		noise::module::Spheres spheres;
		noise::module::Add add;
		noise::module::Select select;

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
