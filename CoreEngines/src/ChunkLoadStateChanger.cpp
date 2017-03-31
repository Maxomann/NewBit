#include "ChunkLoadStateChanger.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::ChunkLoadStateChanger::ChunkLoadStateChanger( sf::Vector3i chunkPosition,
												  ChunkLoadState from,
												  ChunkLoadState to,
												  ChunkLoadState intermediate )
	: chunkPosition( move( chunkPosition ) ),
	from( move( from ) ),
	to( move( to ) ),
	intermediate( move( intermediate ) )
{
}

ChunkLoadState nb::ChunkLoadStateChanger::prepare( World & world )
{
	if (!aborted)
	{
		prepare_internal( world );
		return intermediate;
	}
	else
		return from;
}

void nb::ChunkLoadStateChanger::execute()
{
	if (!aborted)
		future = async( std::launch::async, &ChunkLoadStateChanger::execute_internal, this );
}

ChunkLoadState nb::ChunkLoadStateChanger::finish( World & world )
{
	if (!aborted && isReady())
	{
		finish_internal( world );
		return to;
	}
	else
		return from;
}

void nb::ChunkLoadStateChanger::abort()
{
	aborted = true;
}

bool nb::ChunkLoadStateChanger::isAborted()const
{
	return aborted;
}

bool nb::ChunkLoadStateChanger::isReady()const
{
	if (!future.valid())
		return true;
	else if (future.wait_for( chrono::microseconds( 0 ) ) == future_status::ready)
		return true;
	else
		return false;
}

const sf::Vector3i& nb::ChunkLoadStateChanger::getChunkPosition()const
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

nb::ChunkLoadState nb::ChunkLoadStateChanger::getIntermediate()const
{
	return intermediate;
}
