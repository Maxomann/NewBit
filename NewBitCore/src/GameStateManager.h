#pragma once
#include "GameState.h"

namespace nb
{
	class GameStateManager
	{
		std::queue<std::unique_ptr<GameState>> m_uninitializedStates;
		std::vector<std::unique_ptr<GameState>> m_states;

	public:
		// T must inherit from GameState
		template< class T >
		T* pushState( std::unique_ptr<T>&& ptr )
		{
			m_uninitializedStates.push( std::move( ptr ) );
			return static_cast<T*>(m_uninitializedStates.back().get());
		}

		DLL_EXPORT void initNewStates( const CoreRef& core );

		DLL_EXPORT void checkDestroyGameStates();

		DLL_EXPORT void destroy_all();
	};
}
