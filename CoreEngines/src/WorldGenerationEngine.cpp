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

	auto sand = r_resourceEngine->textures.getTextureReference( "default:texture:field_sand" );
	auto terrainComp = terrain.addComponent<TerrainComponent>( r_resourceEngine->textures.getTextureReference( "default:texture:field_grass" ),
															   std::map<sf::Vector2i, const TextureReference*>{ make_pair( sf::Vector2i( 0, 0 ),
																														   sand ), make_pair( sf::Vector2i( 1, 1 ),
																																			  sand ), make_pair( sf::Vector2i( 2, 1 ),
																																								 sand ), make_pair( sf::Vector2i( 3, 1 ),
																																													sand ), make_pair( sf::Vector2i( 3, 2 ),
																																																	   sand ) } );

	getCore()->world.addEntity( move( terrain ) );
}
