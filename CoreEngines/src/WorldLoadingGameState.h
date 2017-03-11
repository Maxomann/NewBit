#pragma once
#include "stdafx.h"
#include "RenderSystem.h"
#include "ChunkSystem.h"
#include "WorldGenerationEngine.h"

namespace nb
{
	class WorldLoadingGameState : public GameState
	{
		const CoreRef* r_core;
		WorldGenerationEngine* r_worldGenerationEngine;

		// cameraChunkPositions
		std::map<sf::Vector3i, int> m_cameraChunkPositionCounts;

		void onCameraPositionChanged( const TransformationComponent* transform,
									  sf::Vector3i oldPosition );

		void connectCams( const std::vector<Entity*>& cams );

		// loadedChunks
		std::vector<sf::Vector3i> m_loadedChunks;

		void loadAndUnloadChunks();

	public:
		virtual void init() override;

		virtual void destroy() override;

		virtual bool shouldDestroy() override;

		static const int CHUNK_LOADING_RADIUS;
	};
}
