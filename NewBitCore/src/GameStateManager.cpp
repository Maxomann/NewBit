#include "GameStateManager.h"
using namespace nb;

void nb::GameStateManager::pushState( std::unique_ptr<GameState>&& ptr )
{
	m_uninitializedStates.push_back( move( ptr ) );
}

void nb::GameStateManager::initNewStates( const CoreRefs& coreRefs )
{
	for( auto& ptr : m_uninitializedStates )
	{
		ptr->init( coreRefs );
		m_states.push_back( move( ptr ) );
	}
	m_uninitializedStates.clear();
}

void nb::GameStateManager::checkDestroyGameStates( const CoreRefs& coreRefs )
{
	m_states.erase( std::remove_if( m_states.begin(), m_states.end(), [&] ( std::unique_ptr<GameState>& el ) -> bool{
		if( el->shouldDestroy() )
		{
			el->destroy( coreRefs );
			return true;
		}
		else
			return false;
	} ), m_states.end() );
}

void nb::GameStateManager::clear( const CoreRefs& coreRefs )
{
	for( auto& el : m_states )
		el->destroy( coreRefs );
	m_states.clear();
}
