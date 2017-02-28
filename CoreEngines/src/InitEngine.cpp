#include "InitEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::InitEngine::init()
{
	auto& world = getCore()->world;

	world.addSystem<ChunkSystem>();
}

bool nb::InitEngine::update()
{
	return true;
}
