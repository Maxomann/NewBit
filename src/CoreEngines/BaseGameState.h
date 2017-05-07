#pragma once
#include "stdafx.h"

#include "GraphicsEngine.h"

#include "PositionTrackerComponent.h"

#include "ChunkSystem.h"
#include "PhysicsSystem.h"
#include "TimeSystem.h"
#include "WorldLoadStateSystem.h"
#include "NeedsSystem.h"
#include "RenderSystem.h"

#include "WorldLoadingGameState.h"

namespace nb
{
	class BaseGameState : public GameState
	{
		GraphicsEngine* r_graphicsEngine;

		World world;
		RenderSystem* r_renderSystem;

		Entity* cam;

	public:
		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( GameStateManager& gameStates ) override;

		virtual void destroy( GameStateManager& gameStates ) override;
	};
}
