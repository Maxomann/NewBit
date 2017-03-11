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
	auto ent = r_core->world.createEntity<TransformationComponent, RenderComponent, TerrainComponent>();
	auto renderComponent = ent->getComponent<RenderComponent>();
	renderComponent->setZValue( -10 );
	auto terrain = ent->getComponent<TerrainComponent>();
	auto texRef = r_resourceEngine->textures.getTextureReference( "default:testterrain" );
	terrain->setDebugTexture( *texRef );
	auto transformationComponent = ent->getComponent<TransformationComponent>();
	transformationComponent->setLayer( chunkPosition.z );
	transformationComponent->setPositionXY( Vector2i( ChunkSystem::CHUNK_SIZE_IN_PIXEL * chunkPosition.x,
													  ChunkSystem::CHUNK_SIZE_IN_PIXEL * chunkPosition.y ) );
	transformationComponent->setSize( Vector2u( ChunkSystem::CHUNK_SIZE_IN_PIXEL,
												ChunkSystem::CHUNK_SIZE_IN_PIXEL ) );
}
