#include "CoreEngineManager.h"
using namespace std;
using namespace experimental;

namespace nb
{
	void nb::CoreEngineManager::initEngines()
	{
		for( auto& el : m_enginesVector )
			el->init( *this );
	}

	bool nb::CoreEngineManager::update()
	{
		bool continueRunning = true;
		for( auto& el : m_enginesVector )
			if( !el->update( *this ) )
				continueRunning = false;
		return continueRunning;
	}
}
