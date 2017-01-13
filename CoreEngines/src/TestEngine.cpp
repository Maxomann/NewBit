#include "TestEngine.h"
using namespace std;

nb::TestEngine::TestEngine()
{
	cout << "TestEngine()" << endl;
}

void nb::TestEngine::init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates,
						   World& world )
{
	cout << "TestEngine init()" << endl;

	gameStates.pushState( make_unique<TestGameState>() );

	return;
}

bool nb::TestEngine::update( const CoreEngineManager& coreEngines,
							 GameStateManager& gameStates,
							 World& world )
{
	return true;
}

unsigned int nb::TestEngine::getId() const
{
	cout << "TestEngine getId()" << endl;
	return id::CORE_ENGINE::TEST;
}
