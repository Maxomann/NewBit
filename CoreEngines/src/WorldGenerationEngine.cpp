#include "WorldGenerationEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void WorldGenerationEngine::init()
{
	r_core = getCore();
	r_resourceEngine = r_core->engines.getEngine<ResourceEngine>();
}

bool WorldGenerationEngine::update()
{
	return true;
}

void nb::WorldGenerationEngine::generateChunk( const sf::Vector3i& chunkPosition )
{
	Entity entity;
	entity.addComponent<TransformationComponent>(
		Vector2i( ChunkSystem::CHUNK_SIZE_IN_PIXEL * chunkPosition.x,
				  ChunkSystem::CHUNK_SIZE_IN_PIXEL * chunkPosition.y ),
		chunkPosition.z,
		Vector2u( ChunkSystem::CHUNK_SIZE_IN_PIXEL,
				  ChunkSystem::CHUNK_SIZE_IN_PIXEL )
		);
	entity.addComponent<RenderComponent>( -10 );
	entity.addComponent<TerrainComponent>( *r_resourceEngine->textures.getTextureReference( "default:testterrain" ) );

	getCore()->world.addEntity( move( entity ) );
}
