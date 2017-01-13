#pragma once
#include "stdafx.h"

namespace nb
{
	class TestGameState : public nb::GameState
	{
	public:
		DLL_EXPORT virtual void init( const CoreEngineManager& coreEngines,
									  GameStateManager& gameStates,
									  World& world ) override;

		DLL_EXPORT virtual void destroy( const CoreEngineManager& coreEngines,
										 GameStateManager& gameStates,
										 World& world ) override;

		DLL_EXPORT virtual bool shouldDestroy() override;
	};
}
