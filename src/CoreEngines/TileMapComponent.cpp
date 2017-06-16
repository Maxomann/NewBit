#include "TileMapComponent.h"
#include "ChunkSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

const int TileMapComponent::TILE_SIZE_IN_PIXEL = Tile::TILE_SIZE_IN_PIXEL;
const int TileMapComponent::TERRAIN_SIZE_IN_PIXEL = 640;
const int TileMapComponent::TILES_PER_TERRAIN = 20; // = 640(TERRAIN_SIZE_IN_PIXEL) / 32(TILE_SIZE_IN_PIXEL)

nb::TileMapComponent::TileMapComponent( const Tile* defaultTile )
{
	for( int x = 0; x < TILES_PER_TERRAIN; ++x )
	{
		tiles.emplace_back();
		for( int y = 0; y < TILES_PER_TERRAIN; ++y )
		{
			tiles.at( x ).emplace_back( defaultTile );
		}
	}
}

nb::TileMapComponent::TileMapComponent( const Tile* defaultTile, std::map<sf::Vector2i, const Tile*> tileTexturesByPosition )
{
	for( int x = 0; x < TILES_PER_TERRAIN; ++x )
	{
		tiles.emplace_back();
		for( int y = 0; y < TILES_PER_TERRAIN; ++y )
		{
			tiles.at( x ).emplace_back( defaultTile );
		}
	}
	for( auto& el : tileTexturesByPosition )
		tiles.at( el.first.x ).at( el.first.y ) = el.second;
}

nb::TileMapComponent::TileMapComponent( std::vector<std::vector<const Tile*>> tiles )
	: tiles( move( tiles ) )
{}

void TileMapComponent::init()
{};

void nb::TileMapComponent::setTiles( std::map<sf::Vector2i, const Tile*> tilesByPosition )
{
	for( auto& el : tilesByPosition )
		tiles.at( el.first.x ).at( el.first.y ) = el.second;

	s_tilesChanged.call( getTileData() );
}

const Tile * nb::TileMapComponent::getTile( sf::Vector2i relativePosition ) const
{
	return tiles.at( relativePosition.x ).at( relativePosition.y );
}

const TileMapComponent::TileData& nb::TileMapComponent::getTileData() const
{
	return tiles;
}

sf::Vector2i nb::TileMapComponent::calculateRelativeTilePosition( sf::Vector3i absoluteTilePosition )
{
	Vector2i retVal;

	auto thisPixelPosition = component<TransformationComponent>()->getPosition().asPixelPosition();
	if( thisPixelPosition.z != absoluteTilePosition.z )
		throw std::logic_error( "nb::TileMapComponent::calculateRelativeTilePosition | thisPixelPosition.z != absoluteTilePosition.z" );

	auto thisChunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( thisPixelPosition );

	retVal.x = abs( absoluteTilePosition.x ) % TILES_PER_TERRAIN;

	retVal.y = abs( absoluteTilePosition.y ) % TILES_PER_TERRAIN;

	if( thisChunkPosition.x < 0 && retVal.x != 0 )
		retVal.x = TILES_PER_TERRAIN - retVal.x;
	if( thisChunkPosition.y < 0 && retVal.y != 0 )
		retVal.y = TILES_PER_TERRAIN - retVal.y;

	return retVal;
}
