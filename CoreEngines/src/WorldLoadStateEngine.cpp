#include "WorldLoadStateEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::WorldLoadStateEngine::init()
{
	return;
}

bool nb::WorldLoadStateEngine::update()
{
	return true;
}

bool nb::WorldLoadStateEngine::isChunkLoaded( const sf::Vector3i & chunkPosition )const
{
	return (find( m_loadedChunks.begin(),
				  m_loadedChunks.end(),
				  chunkPosition ) != m_loadedChunks.end());
}

void nb::WorldLoadStateEngine::setChunkLoaded( const sf::Vector3i & chunkPosition, bool isLoaded )
{
	bool stateNow = isChunkLoaded( chunkPosition );

	if (stateNow != isLoaded)
	{
		if (isLoaded)
		{
			m_loadedChunks.push_back( chunkPosition );
		}
		else
		{
			m_loadedChunks.erase( remove_if( m_loadedChunks.begin(), m_loadedChunks.end(), [&]( const Vector3i& el ) {
				return (el == chunkPosition);
			} ), m_loadedChunks.end() );
		}
	}
}

const std::vector<sf::Vector3i>& nb::WorldLoadStateEngine::getLoadedChunks() const
{
	return m_loadedChunks;
}
