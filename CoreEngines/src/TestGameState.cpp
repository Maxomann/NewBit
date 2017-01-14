#include "TestGameState.h"
using namespace std;
using namespace nb;

void TestGameState::init( const CoreRefs& coreRefs )
{
	cout << "TestGameState init()" << endl;
}

void TestGameState::destroy( const CoreRefs& coreRefs )
{
	cout << "TestGameState destroy()" << endl;
}

bool TestGameState::shouldDestroy()
{
	return false;
}
