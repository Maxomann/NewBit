#include "ChunkUnloader.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ChunkUnloader::prepare_internal( World & world )
{}

void nb::ChunkUnloader::execute_internal()
{}

void nb::ChunkUnloader::finish_internal( World & world )
{
	const auto& entitiesInChunk = world.getSystem<ChunkSystem>()->getEntitiesInChunk( chunkPosition );
	auto entities = world.removeEntities_move( entitiesInChunk );
	if( entities.size() )
		coreEngines.getEngine<ChunkCache>()->setCache( move( entities ), chunkPosition );

	//old: world.getSystem<ChunkSystem>()->removeEntitiesInChunk( chunkPosition );
}

nb::ChunkUnloader::ChunkUnloader( sf::Vector3i position, const CoreEngineManager& coreEngines )
	: ChunkLoadStateChanger( position,
							 ChunkLoadState::STATE_LOADED,
							 ChunkLoadState::STATE_UNLOADED,
							 ChunkLoadState::STATE_UNLOADING ),
	coreEngines( coreEngines )
{}
