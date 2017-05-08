#pragma once
#include "stdafx.h"
#include "TextureReference.h"

namespace nb
{
	class Tile
	{
	public:
		using ID = unsigned int;

	private:
		const ID id;

		const std::string name;

		const TextureReference*const texref;

	public:

		Tile( ID tileId,
			  std::string name,
			  const TextureReference* texture );
		Tile( const Tile& ) = delete;//no copy
		Tile( Tile&& ) = default;

		ID getId()const;
		const std::string& getName()const;

		const TextureReference* getTextureReference()const;

		static sf::Vector3i calculateTilePositionForPixelPosition( sf::Vector3i pixelPosition );

		static const int TILE_SIZE_IN_PIXEL;
	};
}
