#include "GameStateManager.h"
using namespace nb;

void nb::GameStateManager::initNewStates()
{
	while (m_uninitializedStates.size() > 0)
	{
		auto& el = m_uninitializedStates.front();
		el->linkToCore( getCore() );
		el->init();
		m_states.push_back( move( el ) );
		m_uninitializedStates.pop_back();
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

void nb::GameStateManager::removeGameState( const GameState* state )
{
	// remove from uninitialized
	m_uninitializedStates.erase( remove_if( m_uninitializedStates.begin(), m_uninitializedStates.end(), [&]( const std::unique_ptr<GameState>& el ) {
		if (state == el.get())
			return true;
		else
			return false;
	} ), m_uninitializedStates.end() );

	// remove from initialized and destroy
	m_states.erase( remove_if( m_states.begin(), m_states.end(), [&]( const std::unique_ptr<GameState>& el ) {
		if (state == el.get())
		{
			el->destroy();
			return true;
		}
		else
			return false;
	} ), m_states.end() );
}

void nb::GameStateManager::update()
{
	for (auto& el : m_states)
		el->update();
}

void nb::GameStateManager::destroy_all()
{
	for (auto& el : m_states)
		el->destroy();
	m_states.clear();
}
