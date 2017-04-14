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
	noiseGenerator.SetFrequency( 1.0 / 25.0 );
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
				if (noiseVal > 0.4 && dist2( mt ) < 1)
				{
					sf::Vector3i placementPosition(
						(positionInTilesX*TileMapComponent::TILE_SIZE_IN_PIXEL) + TileMapComponent::TILE_SIZE_IN_PIXEL / 2,
						(positionInTilesY*TileMapComponent::TILE_SIZE_IN_PIXEL) + TileMapComponent::TILE_SIZE_IN_PIXEL / 2,
						chunkPosition.z );

					retVal.push_back( createTree( engines(), placementPosition ) );
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

	retVal.push_back( createTilemapChunk( engines(), chunkPosition, move( tiles ) ) );

	return retVal;
}
