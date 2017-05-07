#pragma once
#include "stdafx.h"
#include "RenderSystem.h"
#include "ChunkSystem.h"
#include "WorldGenerationEngine.h"
#include "WorldLoadStateSystem.h"
#include "ChunkLoader.h"
#include "ChunkUnloader.h"
#include "ChunkCache.h"

namespace nb
{
	class WorldLoadingGameState : public GameState
	{
		const CoreRef* r_core;
		WorldLoadStateSystem* r_worldLoadStateSystem;
		WorldGenerationEngine* r_worldGenerationEngine;
		ChunkSystem* r_chunkSystem;

		ChunkCache chunkCache;

		// cameraChunkPositions
		std::map<sf::Vector3i, int> m_cameraChunkPositionCounts;

		void onCameraPositionChanged( const TransformationComponent* transform,
									  sf::Vector3i oldPosition );

		void connectCams( const std::vector<Entity*>& cams );

		void loadAndUnloadChunks();

		Connections m_connections;

	public:
		virtual void init() override;

		virtual void update() override;

		virtual void destroy() override;

		virtual bool shouldDestroy() override;

		static const int CHUNK_LOADING_RADIUS;
	};
}
