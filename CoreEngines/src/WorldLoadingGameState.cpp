#include "WorldLoadingGameState.h"
using namespace std;
using namespace sf;
using namespace nb;

const int WorldLoadingGameState::CHUNK_LOADING_RADIUS = 5;

void nb::WorldLoadingGameState::onCameraPositionChanged( const TransformationComponent * transform,
														 sf::Vector3i oldPosition )
{
	auto oldChunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( oldPosition );
	auto newChunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( transform->getPosition() );

	if (oldChunkPosition != newChunkPosition)
	{
		auto& oldCounter = m_cameraChunkPositionCounts[oldChunkPosition];
		oldCounter -= 1;
		if (oldCounter < 0)
			m_cameraChunkPositionCounts.erase( oldChunkPosition );

		m_cameraChunkPositionCounts[newChunkPosition] += 1;
	}

	loadAndUnloadChunks();
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
	// TODO
}

void nb::WorldLoadingGameState::init()
{
	r_core = getCore();
	r_worldGenerationEngine = r_core->engines.getEngine<WorldGenerationEngine>();

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
