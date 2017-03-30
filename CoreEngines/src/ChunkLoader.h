#pragma once
#include "stdafx.h"
#include "ChunkLoadStateChanger.h"
#include "WorldGenerationEngine.h"

namespace nb
{
	class ChunkLoader : public ChunkLoadStateChanger
	{
		std::vector<Entity> entities;

	protected:
		virtual void prepare_internal( const CoreEngineManager& coreEngines,
									   World& world ) override;

		virtual void execute_internal( const CoreEngineManager& coreEngines ) override;

		virtual void finish_internal( const CoreEngineManager& coreEngines,
									  World& world ) override;

	public:
		ChunkLoader( sf::Vector3i position );
	};
}
