#include "TestEngine.h"
using namespace std;

nb::TestEngine::TestEngine()
{
	cout << "TestEngine()" << endl;
}

void nb::TestEngine::init( const CoreRefs& coreRefs )
{
	cout << "TestEngine init()" << endl;

	coreRefs.gameStates.pushState( make_unique<TestGameState>() );

	return;
}

bool nb::TestEngine::update( const CoreRefs& coreRefs )
{
	return true;
}

unsigned int nb::TestEngine::getId() const
{
	cout << "TestEngine getId()" << endl;
	return id::CORE_ENGINE::TEST;
}
