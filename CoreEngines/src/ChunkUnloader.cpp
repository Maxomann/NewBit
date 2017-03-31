#include "ChunkUnloader.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ChunkUnloader::prepare_internal( World & world )
{
}

void nb::ChunkUnloader::execute_internal()
{
}

void nb::ChunkUnloader::finish_internal( World & world )
{
	world.getSystem<ChunkSystem>()->removeEntitiesInChunk( chunkPosition );
}

nb::ChunkUnloader::ChunkUnloader( sf::Vector3i position )
	: ChunkLoadStateChanger( position,
							 ChunkLoadState::STATE_LOADED,
							 ChunkLoadState::STATE_UNLOADED,
							 ChunkLoadState::STATE_UNLOADING )
{
}
