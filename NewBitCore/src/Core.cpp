#include "Core.h"
using namespace std;

void nb::Core::run()
{
	const CoreRef coreRef( m_engines, m_gameStates, m_world );

	//init
	m_engines.loadFromFolder( "./bin" );

	m_engines.initEngines( coreRef );

	//main loop
	while (m_engines.update( coreRef ))
	{
		m_gameStates.checkDestroyGameStates( coreRef );
		m_gameStates.initNewStates( coreRef );
		m_world.update();
	};

	m_gameStates.clear( coreRef );
}
