#include "ChunkLoader.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ChunkLoader::prepare_internal( const CoreEngineManager & coreEngines, World & world )
{
}

void nb::ChunkLoader::execute_internal( const CoreEngineManager & coreEngines )
{
	entities = coreEngines.getEngine<WorldGenerationEngine>()->generateChunk( chunkPosition );
}

void nb::ChunkLoader::finish_internal( const CoreEngineManager & coreEngines, World & world )
{
	world.addEntities( move( entities ) );
}

nb::ChunkLoader::ChunkLoader( sf::Vector3i position )
	: ChunkLoadStateChanger( position,
							 ChunkLoadState::STATE_UNLOADED,
							 ChunkLoadState::STATE_LOADED,
							 ChunkLoadState::STATE_LOADING )
{
}
