#pragma once
#include "GameState.h"

namespace nb
{
	class GameStateManager : public CoreRefContainer
	{
		std::list<std::unique_ptr<GameState>> m_uninitializedStates;
		std::vector<std::unique_ptr<GameState>> m_states;

	public:
		template< class T >
		void pushState( std::unique_ptr<T>&& ptr )
		{
			m_uninitializedStates.push_back( std::move( ptr ) );
		}

		// T must inherit from GameState
		template< class T >
		T* pushState_instant( std::unique_ptr<T>&& ptr )
		{
			ptr->linkToCore( getCore() );
			ptr->init();
			m_states.push_back( std::move( ptr ) );
			return static_cast<T*>(m_states.back().get());
		}

		void initNewStates();

		void checkDestroyGameStates();

		DLL_EXPORT void removeGameState( const GameState* state );

		void update();

		void destroy_all();
	};
}
