#include "ChunkCacheEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ChunkCacheEngine::init()
{
}

bool nb::ChunkCacheEngine::update()
{
	return true;
}

void nb::ChunkCacheEngine::setCache( std::vector<Entity>&& entities,
									 sf::Vector3i chunkPosition )
{
	cache[chunkPosition] = move( entities );
}

std::vector<Entity> nb::ChunkCacheEngine::getCache( sf::Vector3i chunkPosition )
{
	auto found = cache.find( chunkPosition );

	if (found != cache.end())
	{
		auto retVal = move( found->second );
		cache.erase( found );
		return retVal;
	}
	else
		return std::vector<Entity>();
}

bool nb::ChunkCacheEngine::hasCache( sf::Vector3i chunkPosition ) const
{
	auto found = cache.find( chunkPosition );
	return (found != cache.end());
}
