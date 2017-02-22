#include "GameStateManager.h"
using namespace nb;

void nb::GameStateManager::pushState( std::unique_ptr<GameState>&& ptr )
{
	m_uninitializedStates.push_back( move( ptr ) );
}

void nb::GameStateManager::initNewStates( const CoreRef& core )
{
	for (auto& ptr : m_uninitializedStates)
	{
		ptr->linkToCore( &core );
		ptr->init();
		m_states.push_back( move( ptr ) );
	}
	m_uninitializedStates.clear();
}

void nb::GameStateManager::checkDestroyGameStates()
{
	m_states.erase( std::remove_if( m_states.begin(), m_states.end(), [&]( std::unique_ptr<GameState>& el ) -> bool {
		if (el->shouldDestroy())
		{
			el->destroy();
			return true;
		}
		else
			return false;
	} ), m_states.end() );
}

void nb::GameStateManager::clear()
{
	for (auto& el : m_states)
		el->destroy();
	m_states.clear();
}
