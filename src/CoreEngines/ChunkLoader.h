#pragma once
#include "stdafx.h"
#include "ChunkLoadStateChanger.h"
#include "ChunkCache.h"
#include "WorldGenerator.h"

namespace nb
{
	class ChunkLoader : public ChunkLoadStateChanger
	{
		const std::shared_ptr<const WorldGenerator> chunkGenerator;
		ChunkCache& chunkCache;

		std::vector<Entity> entities;

		bool loadFromCache = false;

	protected:
		virtual void prepare_internal( World& world ) override;

		virtual void execute_internal() override;

		virtual void finish_internal( World& world ) override;

	public:
		ChunkLoader( const std::shared_ptr<const WorldGenerator>& chunkGenerator,
					 ChunkCache& chunkCache,
					 sf::Vector3i position );
	};
}
