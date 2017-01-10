#include "Core.h"
using namespace std;

void nb::Core::run()
{
	//init
	m_engines.loadFromFolder( "./bin" );

	m_engines.initEngines();

	//main loop
	while( m_engines.update() )
	{
		//m_gameStateManager.update();
		m_world.update();
	};
}