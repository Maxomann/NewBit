#include "Core.h"
using namespace std;

void nb::Core::run()
{
	//init
	m_engines.loadFromFolder( "./bin" );

	m_engines.initEngines( m_engines, m_gameStates, m_world );

	//main loop
	while( m_engines.update( m_engines, m_gameStates, m_world ) )
	{
		m_gameStates.checkDestroyGameStates( m_engines, m_gameStates, m_world );
		m_gameStates.initNewStates( m_engines, m_gameStates, m_world );
		m_world.update();
	};

	m_gameStates.clear( m_engines, m_gameStates, m_world );
}
