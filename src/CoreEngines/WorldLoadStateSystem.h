#pragma once
#include "stdafx.h"
#include "ChunkLoadStateChanger.h"
#include "sfmlExtensions.h"

namespace nb
{
	class WorldLoadStateSystem : public System
	{
		std::map<sf::Vector3i, ChunkLoadState> chunkLoadStates;

		std::vector<std::unique_ptr<ChunkLoadStateChanger>> chunkLoadStateChanger;

		bool isChunkLoadStateChanging( const sf::Vector3i& position );

	public:
		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual void update()override;

		DLL_EXPORT virtual void destroy()override;

		void changeChunkLoadState( std::unique_ptr<ChunkLoadStateChanger> loadStateChanger );
		void abortChunkLoadStateChange( sf::Vector3i position );

		ChunkLoadState getChunkLoadState( const sf::Vector3i& chunkPosition )const;
		const std::map<sf::Vector3i, ChunkLoadState>& getAllChunkLoadStates()const;

		static const int CHUNK_LOAD_STATE_EXECUTIONS_PER_FRAME = 1;
	};
}
