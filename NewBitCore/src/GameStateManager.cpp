#include "GameStateManager.h"
using namespace nb;

void nb::GameStateManager::initNewStates( const CoreRef& core )
{
	while (m_uninitializedStates.size() > 0)
	{
		auto& el = m_uninitializedStates.front();
		el->linkToCore( &core );
		el->init();
		m_states.push_back( move( el ) );
		m_uninitializedStates.pop();
	}
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

void nb::GameStateManager::destroy_all()
{
	for (auto& el : m_states)
		el->destroy();
	m_states.clear();
}
