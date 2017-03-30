#pragma once
#include "stdafx.h"
#include "ChunkLoadState.h"

namespace nb
{
	class ChunkLoadStateChanger
	{
		bool aborted = false;

		std::future<void> future;

	protected:
		const sf::Vector3i chunkPosition;
		const ChunkLoadState from;
		const ChunkLoadState to;
		const ChunkLoadState intermediate;

		// must be thread safe
		virtual void prepareExecute_internal( const CoreEngineManager& coreEngines ) = 0;

		virtual void execute_internal( const CoreEngineManager& coreEngines,
									   World& world ) = 0;

	public:
		ChunkLoadStateChanger( sf::Vector3i chunkPosition,
							   ChunkLoadState from,
							   ChunkLoadState to,
							   ChunkLoadState intermediate );
		virtual ~ChunkLoadStateChanger() = default;

		// return value is the new intermediate ChunkLoadSate for chunkPosition
		ChunkLoadState prepareExecute( const CoreEngineManager& coreEngines );

		// return value is the new ChunkLoadSate for chunkPosition
		ChunkLoadState execute( const CoreEngineManager& coreEngines,
								World& world );

		void abort();
		bool isAborted()const;

		bool isReady()const;

		const sf::Vector3i& getChunkPosition()const;
		ChunkLoadState getFrom()const;
		ChunkLoadState getTo()const;
		ChunkLoadState getIntermediate()const;
	};
}
