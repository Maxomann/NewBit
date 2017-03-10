#include "WorldLoadingGameState.h"
using namespace std;
using namespace sf;
using namespace nb;

const int WorldLoadingGameState::CHUNK_LOADING_RADIUS = 5;

void nb::WorldLoadingGameState::init()
{
	getCore();
}

void nb::WorldLoadingGameState::destroy()
{
}

bool nb::WorldLoadingGameState::shouldDestroy()
{
	return false;
}
