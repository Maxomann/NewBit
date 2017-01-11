#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	class GameState
	{
	public:
		DLL_EXPORT virtual void init( const CoreEngineManager& coreEngines,
									  GameStateManager& gameStates,
									  World& world ) = 0;

		DLL_EXPORT virtual void destroy( const CoreEngineManager& coreEngines,
										 GameStateManager& gameStates,
										 World& world ) = 0;

		DLL_EXPORT virtual bool shouldDestroy() = 0;
	};
}
