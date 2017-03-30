#include "WorldGenerationEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::WorldGenerationEngine::WorldGenerationEngine()
	: mt( rd() ),
	dist( -999999, 999999 ),
	dist2( 0, 10 )
{
	noiseGenerator.SetSeed( dist( mt ) );
	noiseGenerator.SetFrequency( 1.0 / 200.0 );
}

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

	std::vector<std::vector<const TextureReference*>> tiles;

	for (int x = 0; x < TerrainComponent::TILES_PER_TERRAIN; ++x)
	{
		tiles.emplace_back();
		for (int y = 0; y < TerrainComponent::TILES_PER_TERRAIN; ++y)
		{
			double positionInTilesX = static_cast<double>((chunkPosition.x*TerrainComponent::TILES_PER_TERRAIN) + x);
			double positionInTilesY = static_cast<double>((chunkPosition.y*TerrainComponent::TILES_PER_TERRAIN) + y);
			double positionInTilesZ = static_cast<double>(chunkPosition.z);

			auto noiseVal = noiseGenerator.GetValue( positionInTilesX,
													 positionInTilesY,
													 positionInTilesZ );

			if (noiseVal > 0)
			{
				tiles.at( x ).push_back( r_resourceEngine->textures.getTextureReference( "default:texture:field_grass" ) );
				if (noiseVal > 0.8 && dist2( mt ) < 1)
				{
					sf::Vector2i placementPositionXY( positionInTilesX*TerrainComponent::TILE_SIZE_IN_PIXEL,
													  positionInTilesY*TerrainComponent::TILE_SIZE_IN_PIXEL );
					Entity entity;
					entity.addComponent<TransformationComponent>( placementPositionXY,
																  chunkPosition.z,
																  Vector2u( 48 * 2, 64 * 2 ) );
					entity.addComponent<RenderComponent>( 0 );
					entity.addComponent<SpriteComponent>( *r_resourceEngine->textures.getTextureReference( "default:texture:object_tree" ) );
					/* Physics */
					b2BodyDef bodyDef;
					bodyDef.type = b2_staticBody;

					unique_ptr<b2PolygonShape> shape = make_unique<b2PolygonShape>();
					shape->SetAsBox( 0.3f, 0.3f, b2Vec2( 0.f, -0.3f ), 0.f );

					b2FixtureDef fixtureDef;
					fixtureDef.density = 1.0f;
					fixtureDef.friction = 0.3f;

					entity.addComponent<PhysicsComponent>( bodyDef,
														   move( shape ),
														   fixtureDef );

					getCore()->world.addEntity( move( entity ) );
				}
			}
			else if (noiseVal > -0.5)
				tiles.at( x ).push_back( r_resourceEngine->textures.getTextureReference( "default:texture:field_sand" ) );
			else
				tiles.at( x ).push_back( r_resourceEngine->textures.getTextureReference( "default:texture:field_water" ) );
		}
	}

	auto terrainComp = terrain.addComponent<TerrainComponent>( tiles );

	getCore()->world.addEntity( move( terrain ) );
}
