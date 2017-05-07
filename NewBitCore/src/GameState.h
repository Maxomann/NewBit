#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	class GameState
	{
		bool shouldDestroyFlag = false;

	public:
		DLL_EXPORT GameState() = default;
		DLL_EXPORT GameState( const GameState& ) = delete;
		DLL_EXPORT GameState( GameState&& ) = delete;
		DLL_EXPORT virtual ~GameState() = default;

		DLL_EXPORT virtual void init( const CoreEngineManager& coreEngines,
									  GameStateManager& gameStates ) = 0;

		DLL_EXPORT virtual void update( const CoreEngineManager& coreEngines,
										GameStateManager& gameStates ) = 0;

		DLL_EXPORT virtual void destroy( const CoreEngineManager& coreEngines,
										 GameStateManager& gameStates ) = 0;

		bool shouldDestroy()const
		{
			return shouldDestroyFlag;
		};

		DLL_EXPORT void close()
		{
			shouldDestroyFlag = true;
		}
	};

	/*
	virtual void init( const CoreEngineManager& coreEngines,
					   GameStateManager& gameStates ) override;

	virtual void update( const CoreEngineManager& coreEngines,
						 GameStateManager& gameStates ) override;

	virtual void destroy( const CoreEngineManager& coreEngines,
						  GameStateManager& gameStates ) override;
	*/
}
