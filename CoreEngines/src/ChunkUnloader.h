#pragma once
#include "stdafx.h"
#include "ChunkLoadStateChanger.h"
#include "ChunkSystem.h"

namespace nb
{
	class ChunkUnloader : public ChunkLoadStateChanger
	{
	protected:
		virtual void prepareExecute_internal( const CoreEngineManager& coreEngines ) override;

		virtual void execute_internal( const CoreEngineManager& coreEngines,
									   World& world ) override;

	public:
		ChunkUnloader( sf::Vector3i position );
	};
}
