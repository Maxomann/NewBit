#pragma once
#include "stdafx.h"
#include "CoreRefs.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	class GameState
	{
	public:
		DLL_EXPORT virtual void init( const CoreRefs& coreRefs ) = 0;

		DLL_EXPORT virtual void destroy( const CoreRefs& coreRefs ) = 0;

		DLL_EXPORT virtual bool shouldDestroy() = 0;
	};
}
