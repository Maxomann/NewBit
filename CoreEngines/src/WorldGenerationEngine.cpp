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
	Entity terrain;
	terrain.addComponent<TransformationComponent>(
		Vector2i( ChunkSystem::CHUNK_SIZE_IN_PIXEL * chunkPosition.x,
				  ChunkSystem::CHUNK_SIZE_IN_PIXEL * chunkPosition.y ),
		chunkPosition.z,
		Vector2u( ChunkSystem::CHUNK_SIZE_IN_PIXEL,
				  ChunkSystem::CHUNK_SIZE_IN_PIXEL )
		);
	terrain.addComponent<RenderComponent>( -10 );

	std::vector<std::vector<TextureReference>> tiles;

	auto terrainComp = terrain.addComponent<TerrainComponent>( r_resourceEngine->textures.getTextureReference( "default:texture:field_grass" ) );
	terrainComp->setTiles( { make_pair( sf::Vector2i( 0,0 ),
										r_resourceEngine->textures.getTextureReference( "default:texture:field_sand" ) ) } );

	getCore()->world.addEntity( move( terrain ) );
}
