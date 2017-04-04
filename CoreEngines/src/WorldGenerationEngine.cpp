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

std::vector<Entity> nb::WorldGenerationEngine::generateChunk( const sf::Vector3i& chunkPosition )
{
	std::vector<Entity> retVal;

	Entity terrain;
	terrain.addComponent<TransformationComponent>(
		Vector2i( ChunkSystem::CHUNK_SIZE_IN_PIXEL * chunkPosition.x,
				  ChunkSystem::CHUNK_SIZE_IN_PIXEL * chunkPosition.y ),
		chunkPosition.z,
		Vector2f( ChunkSystem::CHUNK_SIZE_IN_PIXEL,
				  ChunkSystem::CHUNK_SIZE_IN_PIXEL )
		);
	terrain.addComponent<RenderComponent>( -10 );

	std::vector<std::vector<const Tile*>> tiles;

	for (int x = 0; x < TileMapComponent::TILES_PER_TERRAIN; ++x)
	{
		tiles.emplace_back();
		for (int y = 0; y < TileMapComponent::TILES_PER_TERRAIN; ++y)
		{
			double positionInTilesX = static_cast<double>((chunkPosition.x*TileMapComponent::TILES_PER_TERRAIN) + x);
			double positionInTilesY = static_cast<double>((chunkPosition.y*TileMapComponent::TILES_PER_TERRAIN) + y);
			double positionInTilesZ = static_cast<double>(std::hash<int>{}(chunkPosition.z));

			auto noiseVal = noiseGenerator.GetValue( positionInTilesX,
													 positionInTilesY,
													 positionInTilesZ );

			if (noiseVal > -0.2)
			{
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 0 ) );
				if (noiseVal > 0.6 && dist2( mt ) < 1)
				{
					sf::Vector2i placementPositionXY(
						(positionInTilesX*TileMapComponent::TILE_SIZE_IN_PIXEL) + TileMapComponent::TILE_SIZE_IN_PIXEL / 2,
						(positionInTilesY*TileMapComponent::TILE_SIZE_IN_PIXEL) + TileMapComponent::TILE_SIZE_IN_PIXEL / 2 );
					Entity entity;
					entity.addComponent<TransformationComponent>( placementPositionXY,
																  chunkPosition.z,
																  Vector2f( 48 * 2, 64 * 2 ) );
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
					retVal.push_back( move( entity ) );
					/*
					Entity entity = r_resourceEngine->blueprints.getEntity( 0 );
					entity->setPosition( {...} );
					entity->setZValue( 0 );
					*/
				}
			}
			else if (noiseVal > -0.5)
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 1 ) );
			else
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 2 ) );
		}
	}

	auto terrainComp = terrain.addComponent<TileMapComponent>( tiles );

	retVal.push_back( move( terrain ) );

	return retVal;
}
