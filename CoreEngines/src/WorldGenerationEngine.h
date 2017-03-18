#pragma once
#include "stdafx.h"
#include "ResourceEngine.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TerrainComponent.h"
#include "ChunkSystem.h"

namespace nb
{
	class WorldGenerationEngine : public CoreEngine
	{
		const CoreRef* r_core;
		ResourceEngine* r_resourceEngine;

	public:
		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual bool update()override;

		DLL_EXPORT void generateChunk( const sf::Vector3i& chunkPosition );
	};
}
