#pragma once
#include "stdafx.h"
#include "ChunkLoadStateChanger.h"
#include "WorldGenerationEngine.h"
#include "ChunkCacheEngine.h"

namespace nb
{
	class ChunkLoader : public ChunkLoadStateChanger
	{
		const CoreEngineManager& coreEngines;

		std::vector<Entity> entities;

		bool loadFromCache = false;

	protected:
		virtual void prepare_internal( World& world ) override;

		virtual void execute_internal() override;

		virtual void finish_internal( World& world ) override;

	public:
		ChunkLoader( sf::Vector3i position, const CoreEngineManager& coreEngines );
	};
}
