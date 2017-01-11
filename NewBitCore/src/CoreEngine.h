#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	class CoreEngine
	{
	public:
		DLL_EXPORT virtual ~CoreEngine() = default;

		DLL_EXPORT virtual void init( const CoreEngineManager& coreEngines,
									  GameStateManager& gameStates,
									  World& world ) = 0;

		// return false to terminate process
		DLL_EXPORT virtual bool update( const CoreEngineManager& coreEngines,
										GameStateManager& gameStates,
										World& world ) = 0;

		DLL_EXPORT virtual unsigned int getId()const = 0;
	};
}
