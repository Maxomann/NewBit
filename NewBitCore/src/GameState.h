#pragma once
#include "stdafx.h"
#include "CoreRef.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	class GameState : public CoreRefContainer
	{
	public:
		GameState() = default;
		GameState( const GameState& ) = delete;
		GameState( GameState&& ) = delete;

		DLL_EXPORT virtual void init() = 0;

		DLL_EXPORT virtual void update() = 0;

		DLL_EXPORT virtual void destroy() = 0;

		DLL_EXPORT virtual bool shouldDestroy() = 0;
	};
}
