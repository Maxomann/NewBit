#include "DefaultWorldGenerator.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::DefaultWorldGenerator::DefaultWorldGenerator( const ResourceEngine*const resourceEngine )
	: r_resourceEngine( resourceEngine )
{
	std::random_device rd;
	std::mt19937 mt( rd() );
	std::uniform_int_distribution<int> dist( -999999, 999999 );

	noiseGenerator.SetSeed( dist( mt ) );
	noiseGenerator.SetFrequency( 1.0 / 140.0 );
}

std::vector<Entity> nb::DefaultWorldGenerator::generateChunk( const sf::Vector3i& chunkPosition )const
{
	std::random_device rd;
	std::mt19937 mt( rd() );
	std::uniform_int_distribution<int> dist2( 0, 19 );

	std::vector<Entity> retVal;

	std::vector<std::vector<const Tile*>> tiles;

	for( int x = 0; x < TileMapComponent::TILES_PER_TERRAIN; ++x )
	{
		tiles.emplace_back();
		for( int y = 0; y < TileMapComponent::TILES_PER_TERRAIN; ++y )
		{
			double positionInTilesX = static_cast<double>( ( chunkPosition.x*TileMapComponent::TILES_PER_TERRAIN ) + x );
			double positionInTilesY = static_cast<double>( ( chunkPosition.y*TileMapComponent::TILES_PER_TERRAIN ) + y );
			double positionInTilesZ = static_cast<double>( std::hash<int>{}( chunkPosition.z ) );

			auto noiseVal = noiseGenerator.GetValue( positionInTilesX,
													 positionInTilesY,
													 positionInTilesZ );

			if( noiseVal > 0.95 )
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 4 ) );
			else if( noiseVal > 0.5 )
			{
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 0 ) );
				if( dist2( mt ) < 1 )
				{
					sf::Vector3i placementPosition(
						( positionInTilesX*TileMapComponent::TILE_SIZE_IN_PIXEL ) + TileMapComponent::TILE_SIZE_IN_PIXEL / 2,
						( positionInTilesY*TileMapComponent::TILE_SIZE_IN_PIXEL ),
						chunkPosition.z );

					EntityFactory::ID entityIdForField = 0;
					if( dist2( mt ) < 2 )
						entityIdForField = 10'000;

					Entity e = r_resourceEngine->entitiyFactories.getFactoryById( entityIdForField )->create( *r_resourceEngine );
					e.getComponent<TransformationComponent>()->setPosition( placementPosition );

					retVal.push_back( move( e ) );
					/*
					Entity entity = r_resourceEngine->blueprints.getEntity( 0 );
					entity->setPosition( {...} );
					entity->setZValue( 0 );
					*/
				}
			}
			else if( noiseVal > 0.4 )
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 0 ) );
			else if( noiseVal > 0.25f )
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 1 ) );
			else if( noiseVal > 0.16f )
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 5 ) );
			else
				tiles.at( x ).push_back( r_resourceEngine->tiles.getTile( 2 ) );
		}
	}

	retVal.push_back( createTilemapChunk( r_resourceEngine, chunkPosition, move( tiles ) ) );

	return retVal;
}
