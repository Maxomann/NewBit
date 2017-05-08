#include "WorldLoadingGameState.h"
using namespace std;
using namespace sf;
using namespace nb;

const int WorldLoadingGameState::CHUNK_LOADING_RADIUS = 2;

nb::WorldLoadingGameState::WorldLoadingGameState( World& world, Entity* camera )
	: world( world ),
	camera( camera )
{}

void nb::WorldLoadingGameState::onCameraPositionChanged( const TransformationComponent * transform,
														 sf::Vector3i oldPosition )
{
	auto oldChunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( oldPosition );
	auto newChunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( transform->getPosition() );

	if( oldChunkPosition != newChunkPosition )
	{
		auto& oldCounter = m_cameraChunkPositionCounts[ oldChunkPosition ];
		oldCounter -= 1;
		if( oldCounter < 1 )
			m_cameraChunkPositionCounts.erase( oldChunkPosition );

		m_cameraChunkPositionCounts[ newChunkPosition ] += 1;
	}
}

void nb::WorldLoadingGameState::connectCams( const std::vector<Entity*>& cams )
{
	m_cameraChunkPositionCounts.clear();

	for( const auto& el : cams )
	{
		auto transform = el->getComponent<TransformationComponent>();
		transform->s_positionChanged.connect_track( m_connections,
													this,
													&WorldLoadingGameState::onCameraPositionChanged );

		// first time init m_cameraChunkPositionCounts
		auto chunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( transform->getPosition() );
		m_cameraChunkPositionCounts[ chunkPosition ] += 1;
	}
}

void nb::WorldLoadingGameState::loadAndUnloadChunks()
{
	vector<Vector3i> chunksThatShouldBeLoaded;
	for( const auto& el : m_cameraChunkPositionCounts )
	{
		if( el.second > 0 )
		{
			for( int x = -1 * CHUNK_LOADING_RADIUS; x <= CHUNK_LOADING_RADIUS; ++x )
			{
				for( int y = -1 * CHUNK_LOADING_RADIUS; y <= CHUNK_LOADING_RADIUS; ++y )
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
	auto chunkLoadStateCopy = r_worldLoadStateSystem->getAllChunkLoadStates();
	for( const auto& el : chunkLoadStateCopy )
	{
		if( el.second == ChunkLoadState::STATE_LOADED ||
			el.second == ChunkLoadState::STATE_LOADING )
		{
			auto it = find( chunksThatShouldBeLoaded.begin(), chunksThatShouldBeLoaded.end(), el.first );
			if( it == chunksThatShouldBeLoaded.end() )
			{
				if( el.second == ChunkLoadState::STATE_LOADED )
				{
					r_worldLoadStateSystem->changeChunkLoadState( make_unique<ChunkUnloader>( chunkCache,
																							  el.first ) );
				}
				else if( el.second == ChunkLoadState::STATE_LOADING )
				{
					r_worldLoadStateSystem->abortChunkLoadStateChange( el.first );
				}
				else
					throw std::logic_error( "big mistake here" );
			}
		}
	}

	//load
	for( const auto& el : chunksThatShouldBeLoaded )
	{
		auto loadState = r_worldLoadStateSystem->getChunkLoadState( el );

		//is not loaded
		if( loadState == ChunkLoadState::STATE_UNLOADED )
		{
			//load
			r_worldLoadStateSystem->changeChunkLoadState( make_unique<ChunkLoader>( chunkGenerator,
																					chunkCache,
																					el ) );
		}
		else if( loadState == ChunkLoadState::STATE_UNLOADING )
		{
			r_worldLoadStateSystem->abortChunkLoadStateChange( el );
		}
	}
}

void nb::WorldLoadingGameState::init( const CoreEngineManager& coreEngines,
									  GameStateManager& gameStates )
{
	chunkGenerator = make_shared<DefaultWorldGenerator>( coreEngines.getEngine<ResourceEngine>() );

	r_worldLoadStateSystem = world.getSystem<WorldLoadStateSystem>();

	connectCams( {camera} );
}

void nb::WorldLoadingGameState::update( GameStateManager& gameStates )
{
	loadAndUnloadChunks();
}

void nb::WorldLoadingGameState::destroy( GameStateManager& gameStates )
{}
