#include "TestEngine.h"
using namespace std;

nb::TestEngine::TestEngine()
{
	cout << "TestEngine()" << endl;
}

void nb::TestEngine::init( const CoreRef& coreRefs )
{
	cout << "TestEngine init()" << endl;

	coreRefs.gameStates.pushState( make_unique<TestGameState>() );

	return;
}

bool nb::TestEngine::update( const CoreRef& coreRefs )
{
	return true;
}
