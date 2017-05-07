#pragma once
#include "stdafx.h"

#include "ChunkSystem.h"
#include "PhysicsSystem.h"
#include "TimeSystem.h"
#include "WorldLoadStateSystem.h"
#include "NeedsSystem.h"
#include "RenderSystem.h"

namespace nb
{
	class BaseGameState : public GameState
	{
		World world;

	public:
		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( const CoreEngineManager& coreEngines,
							 GameStateManager& gameStates ) override;

		virtual void destroy( const CoreEngineManager& coreEngines,
							  GameStateManager& gameStates ) override;
	}
}
