#include "TestEngine.h"
using namespace std;

nb::TestEngine::TestEngine()
{
	cout << "TestEngine()" << endl;
}

void nb::TestEngine::init( const CoreRef& core )
{
	cout << "TestEngine init()" << endl;

	core.gameStates.pushState( make_unique<TestGameState>() );

	return;
}

bool nb::TestEngine::update( const CoreRef& core )
{
	return true;
}
