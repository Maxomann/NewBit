#include "Tile.h"
using namespace std;
using namespace sf;
using namespace nb;

const int Tile::TILE_SIZE_IN_PIXEL = 32;

nb::Tile::Tile( ID tileId,
				std::string name,
				const TextureReference * texture )
	:id( tileId ),
	name( name ),
	texref( texture )
{
}

Tile::ID nb::Tile::getId() const
{
	return id;
}

const std::string & nb::Tile::getName() const
{
	return name;
}

const TextureReference * nb::Tile::getTextureReference() const
{
	return texref;
}

sf::Vector3i nb::Tile::calculateTilePositionForPixelPosition( sf::Vector3i pixelPosition )
{
	auto remainX = pixelPosition.x % TILE_SIZE_IN_PIXEL;
	auto remainY = pixelPosition.y % TILE_SIZE_IN_PIXEL;

	auto x = (pixelPosition.x - remainX) / TILE_SIZE_IN_PIXEL;
	auto y = (pixelPosition.y - remainY) / TILE_SIZE_IN_PIXEL;

	if (pixelPosition.x < 0 && remainX != 0)
		x -= 1;

	if (pixelPosition.y < 0 && remainY != 0)
		y -= 1;

	return Vector3i( x, y, pixelPosition.z );
}
