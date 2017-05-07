#include "ChunkLoader.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ChunkLoader::prepare_internal( World & world )
{
	if( chunkCache.hasCache( chunkPosition ) )
	{
		loadFromCache = true;
		entities = chunkCache.getCache( chunkPosition );
	}
}

void nb::ChunkLoader::execute_internal()
{
	if( !loadFromCache )
		entities = chunkGenerator->generateChunk( chunkPosition );
}

void nb::ChunkLoader::finish_internal( World & world )
{
	world.addEntities( move( entities ) );
}

nb::ChunkLoader::ChunkLoader( const std::shared_ptr<const WorldGenerator>& chunkGenerator,
							  ChunkCache & chunkCache,
							  sf::Vector3i position )
	: ChunkLoadStateChanger( position,
							 ChunkLoadState::STATE_UNLOADED,
							 ChunkLoadState::STATE_LOADED,
							 ChunkLoadState::STATE_LOADING ),
	chunkGenerator( chunkGenerator ),
	chunkCache( chunkCache )
{}
