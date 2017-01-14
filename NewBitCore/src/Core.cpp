#include "Core.h"
using namespace std;

void nb::Core::run()
{
	const CoreRefs coreRefs( m_engines, m_gameStates, m_world );

	//init
	m_engines.loadFromFolder( "./bin" );

	m_engines.initEngines( coreRefs );

	//main loop
	while( m_engines.update( coreRefs ) )
	{
		m_gameStates.checkDestroyGameStates( coreRefs );
		m_gameStates.initNewStates( coreRefs );
		m_world.update();
	};

	m_gameStates.clear( coreRefs );
}
