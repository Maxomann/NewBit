#include "Tile.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::Tile::Tile( ID tileId, const TextureReference * texture )
	:id( tileId ),
	texref( texture )
{
}

Tile::ID nb::Tile::getId() const
{
	return id;
}

const TextureReference * nb::Tile::getTextureReference() const
{
	return texref;
}
