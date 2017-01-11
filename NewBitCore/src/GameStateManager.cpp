#include "GameStateManager.h"
using namespace nb;

void nb::GameStateManager::pushState( std::unique_ptr<GameState>&& ptr )
{
	m_uninitializedStates.push_back( move( ptr ) );
}

void nb::GameStateManager::initNewStates( const CoreEngineManager& coreEngines,
										  GameStateManager& gameStates,
										  World& world )
{
	for( auto& ptr : m_uninitializedStates )
	{
		ptr->init( coreEngines, gameStates, world );
		m_states.push_back( move( ptr ) );
	}
	m_uninitializedStates.clear();
}

void nb::GameStateManager::checkDestroyGameStates( const CoreEngineManager & coreEngines,
												   GameStateManager & gameStates,
												   World & world )
{
	m_states.erase( std::remove_if( m_states.begin(), m_states.end(), [&] ( std::unique_ptr<GameState>& el ) -> bool{
		if( el->shouldDestroy() )
		{
			el->destroy( coreEngines, gameStates, world );
			return true;
		}
		else
			return false;
	} ), m_states.end() );
}
