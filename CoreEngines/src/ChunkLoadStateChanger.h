#pragma once
#include "stdafx.h"
#include "ChunkLoadState.h"

namespace nb
{
	class ChunkLoadStateChanger
	{
	protected:
		const sf::Vector3i chunkPosition;
		const ChunkLoadState from;
		const ChunkLoadState to;

	public:
		ChunkLoadStateChanger( sf::Vector3i chunkPosition,
							   ChunkLoadState from,
							   ChunkLoadState to );

		// must be thread safe
		virtual void prepareExecute( const CoreEngineManager& coreEngines ) = 0;
		virtual void execute( const CoreEngineManager& coreEngines,
							  World& world ) = 0;

		sf::Vector3i getChunkPosition()const;
		ChunkLoadState getFrom()const;
		ChunkLoadState getTo()const;
	};
}
