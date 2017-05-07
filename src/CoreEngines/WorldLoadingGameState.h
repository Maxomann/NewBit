#pragma once
#include "stdafx.h"
#include "RenderSystem.h"
#include "ChunkSystem.h"
#include "DefaultWorldGenerator.h"
#include "WorldLoadStateSystem.h"
#include "ChunkLoader.h"
#include "ChunkUnloader.h"
#include "ChunkCache.h"

namespace nb
{
	class WorldLoadingGameState : public GameState
	{
		WorldLoadStateSystem* r_worldLoadStateSystem;
		ChunkSystem* r_chunkSystem;

		ChunkCache chunkCache;
		std::shared_ptr<WorldGenerator> chunkGenerator;

		// cameraChunkPositions
		std::map<sf::Vector3i, int> m_cameraChunkPositionCounts;

		void onCameraPositionChanged( const TransformationComponent* transform,
									  sf::Vector3i oldPosition );

		void connectCams( const std::vector<Entity*>& cams );

		void loadAndUnloadChunks();

		Connections m_connections;

	public:
		WorldLoadingGameState();

		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( GameStateManager& gameStates ) override;

		virtual void destroy( GameStateManager& gameStates ) override;

		static const int CHUNK_LOADING_RADIUS;
	};
}
