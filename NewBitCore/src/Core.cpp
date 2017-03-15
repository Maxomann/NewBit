#include "Core.h"
using namespace std;

void nb::Core::run()
{
	const CoreRef coreRef( m_engines, m_gameStates, m_world );

	//init
	m_engines.loadFromFolder( "./bin" );

	m_engines.initEngines( coreRef );
	m_world.initSystems();

	//main loop
	while (m_engines.update())
	{
		m_gameStates.checkDestroyGameStates();
		m_gameStates.initNewStates( coreRef );
		m_gameStates.update();
		m_world.update();
	};

	m_gameStates.destroy_all();
}
