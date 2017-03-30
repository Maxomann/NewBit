#include "WorldLoadStateEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

bool nb::WorldLoadStateEngine::isChunkLoadStateChanging( const sf::Vector3i & position )
{
	for (auto& el : chunkLoadStateChanger)
		if (el->getChunkPosition() == position &&
			 !el->isAborted())
			return true;
	return false;
}

void nb::WorldLoadStateEngine::init()
{
	return;
}

bool nb::WorldLoadStateEngine::update()
{
	chunkLoadStateChanger.erase( remove_if( chunkLoadStateChanger.begin(), chunkLoadStateChanger.end(), [&]( const unique_ptr<ChunkLoadStateChanger>& el ) {
		if (el->isReady())
		{
			chunkLoadStates[el->getChunkPosition()] = el->finish( engines(), world() );
			return true;
		}
		else
			return false;
	} ), chunkLoadStateChanger.end() );

	// remove_if on map
	for (auto iter = chunkLoadStates.begin(); iter != chunkLoadStates.end(); ) {
		if (iter->second == ChunkLoadState::STATE_UNLOADED) {
			iter = chunkLoadStates.erase( iter );
		}
		else {
			++iter;
		}
	}

	return true;
}

void nb::WorldLoadStateEngine::changeChunkLoadState( std::unique_ptr<ChunkLoadStateChanger> loadStateChanger )
{
	if (isChunkLoadStateChanging( loadStateChanger->getChunkPosition() ))
		throw logic_error( "ChunkLoadState is already changing" );
	else if (!loadStateChanger->isAborted())
	{
		chunkLoadStateChanger.push_back( move( loadStateChanger ) );
		auto& newPtr = chunkLoadStateChanger.back();
		if (getChunkLoadState( newPtr->getChunkPosition() ) != newPtr->getFrom())
			throw logic_error( "ChunkLoadState getFrom() does not match" );
		chunkLoadStates[newPtr->getChunkPosition()] = newPtr->prepare( engines(), world() );
		// launches a thread
		newPtr->execute( engines() );
	}
}

void nb::WorldLoadStateEngine::abortChunkLoadStateChange( sf::Vector3i position )
{
	for (auto& el : chunkLoadStateChanger)
		if (el->getChunkPosition() == position)
			el->abort();
}

ChunkLoadState nb::WorldLoadStateEngine::getChunkLoadState( const sf::Vector3i & chunkPosition ) const
{
	auto found = chunkLoadStates.find( chunkPosition );
	if (found != chunkLoadStates.end())
		return found->second;
	else
		return ChunkLoadState::STATE_UNLOADED;
}

const std::map<sf::Vector3i, ChunkLoadState>& nb::WorldLoadStateEngine::getAllChunkLoadStates() const
{
	return chunkLoadStates;
}
