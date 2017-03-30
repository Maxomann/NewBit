#include "ChunkLoadStateChanger.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::ChunkLoadStateChanger::ChunkLoadStateChanger( sf::Vector3i chunkPosition,
												  ChunkLoadState from,
												  ChunkLoadState to )
	: chunkPosition( chunkPosition ),
	from( from ),
	to( to )
{
}

sf::Vector3i nb::ChunkLoadStateChanger::getChunkPosition()const
{
	return chunkPosition;
}
nb::ChunkLoadState nb::ChunkLoadStateChanger::getFrom()const
{
	return from;
}
nb::ChunkLoadState nb::ChunkLoadStateChanger::getTo()const
{
	return to;
}
