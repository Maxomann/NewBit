#include "WorldLoadingGameState.h"
using namespace std;
using namespace sf;
using namespace nb;

const int WorldLoadingGameState::CHUNK_LOADING_RADIUS = 2;

void nb::WorldLoadingGameState::onCameraPositionChanged( const TransformationComponent * transform,
														 sf::Vector3i oldPosition )
{
	auto oldChunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( oldPosition );
	auto newChunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( transform->getPosition() );

	if (oldChunkPosition != newChunkPosition)
	{
		auto& oldCounter = m_cameraChunkPositionCounts[oldChunkPosition];
		oldCounter -= 1;
		if (oldCounter < 1)
			m_cameraChunkPositionCounts.erase( oldChunkPosition );

		m_cameraChunkPositionCounts[newChunkPosition] += 1;
		loadAndUnloadChunks();
	}
}

void nb::WorldLoadingGameState::connectCams( const std::vector<Entity*>& cams )
{
	m_cameraChunkPositionCounts.clear();

	for (const auto& el : cams)
	{
		auto transform = el->getComponent<TransformationComponent>();
		transform->s_positionChanged.connect_mem_fn_auto_track( &WorldLoadingGameState::onCameraPositionChanged,
																*this );

		// first time init m_cameraChunkPositionCounts
		auto chunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( transform->getPosition() );
		m_cameraChunkPositionCounts[chunkPosition] += 1;
	}

	loadAndUnloadChunks();
}

void nb::WorldLoadingGameState::loadAndUnloadChunks()
{
	vector<Vector3i> chunksThatShouldBeLoaded;
	for (const auto& el : m_cameraChunkPositionCounts)
	{
		if (el.second > 0)
		{
			for (int x = -1 * CHUNK_LOADING_RADIUS; x <= CHUNK_LOADING_RADIUS; ++x)
			{
				for (int y = -1 * CHUNK_LOADING_RADIUS; y <= CHUNK_LOADING_RADIUS; ++y)
				{
					auto camPosition = el.first;
					camPosition.x += x;
					camPosition.y += y;
					chunksThatShouldBeLoaded.push_back( camPosition );
				}
			}
		}
	}

	//unique chunksThatShouldBeLoaded
	sort( chunksThatShouldBeLoaded.begin(), chunksThatShouldBeLoaded.end() );
	chunksThatShouldBeLoaded.erase( unique( chunksThatShouldBeLoaded.begin(), chunksThatShouldBeLoaded.end() ), chunksThatShouldBeLoaded.end() );

	//unload
	auto loadedChunksCopy = r_worldLoadStateEngine->getLoadedChunks();
	for (const auto& el : loadedChunksCopy)
	{
		auto it = find( chunksThatShouldBeLoaded.begin(), chunksThatShouldBeLoaded.end(), el );
		if (it == chunksThatShouldBeLoaded.end())
		{
			r_chunkSystem->removeEntitiesInChunk( el );
			r_worldLoadStateEngine->setChunkLoaded( el, false );
		}
	}

	//load
	for (const auto& el : chunksThatShouldBeLoaded)
	{
		//is not loaded
		if (!r_worldLoadStateEngine->isChunkLoaded( el ))
		{
			//load
			r_worldGenerationEngine->generateChunk( el );
			r_worldLoadStateEngine->setChunkLoaded( el, true );
		}
	}
}

void nb::WorldLoadingGameState::init()
{
	r_core = getCore();
	r_worldLoadStateEngine = r_core->engines.getEngine<WorldLoadStateEngine>();
	r_worldGenerationEngine = r_core->engines.getEngine<WorldGenerationEngine>();
	r_chunkSystem = r_core->world.getSystem<ChunkSystem>();

	auto renderSystem = r_core->world.getSystem<RenderSystem>();
	renderSystem->s_camerasForDrawingChanged.connect_mem_fn_auto_track( &WorldLoadingGameState::connectCams,
																		*this );
	connectCams( renderSystem->getCamerasForDrawing() );
}

void nb::WorldLoadingGameState::destroy()
{
}

bool nb::WorldLoadingGameState::shouldDestroy()
{
	return false;
}
