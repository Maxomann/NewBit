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

		virtual void prepare_internal( World& world ) = 0;

		// must be thread safe
		virtual void execute_internal() = 0;

		virtual void finish_internal( World& world ) = 0;

	public:
		ChunkLoadStateChanger( sf::Vector3i chunkPosition,
							   ChunkLoadState from,
							   ChunkLoadState to,
							   ChunkLoadState intermediate );
		virtual ~ChunkLoadStateChanger() = default;

		// return value is the new intermediate ChunkLoadSate for chunkPosition
		ChunkLoadState prepare( World& world );

		// internal execution happens in a thread
		void execute();

		// return value is the new ChunkLoadSate for chunkPosition
		ChunkLoadState finish( World& world );

		void abort();
		bool isAborted()const;

		bool isReady()const;

		const sf::Vector3i& getChunkPosition()const;
		ChunkLoadState getFrom()const;
		ChunkLoadState getTo()const;
		ChunkLoadState getIntermediate()const;
	};
}
