#include "TestGameState.h"
using namespace std;
using namespace nb;

void TestGameState::init( const CoreEngineManager& coreEngines,
						  GameStateManager& gameStates,
						  World& world )
{
	cout << "TestGameState init()" << endl;
}

void TestGameState::destroy( const CoreEngineManager& coreEngines,
							 GameStateManager& gameStates,
							 World& world )
{
	cout << "TestGameState destroy()" << endl;
}

bool TestGameState::shouldDestroy()
{
	return false;
}
