#pragma once
#include "GameState.h"

namespace nb
{
	class GameStateManager
	{
		std::vector<std::unique_ptr<GameState>> m_uninitializedStates;
		std::vector<std::unique_ptr<GameState>> m_states;

	public:
		DLL_EXPORT void pushState( std::unique_ptr<GameState>&& ptr );

		DLL_EXPORT void initNewStates( const CoreRef& core );

		DLL_EXPORT void checkDestroyGameStates();

		DLL_EXPORT void clear();
	};
}
