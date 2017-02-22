#include "ChunkSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

const int ChunkSystem::CHUNK_SIZE_IN_PIXEL = 640;

void nb::ChunkSystem::init()
{
	r_world = getWorld();
	//r_world->s_onEntityAdded.connect_mem_fn_auto( &ChunkSystem::onEntityAdded, *this );
	//r_world->s_onEntitiesRemoved.connect_mem_fn_auto( &ChunkSystem::onEntitiesRemoved, *this );
}
