#pragma once
#include "stdafx.h"
#include "TextureManager.h"
#include "Tile.h"

namespace nb
{
	class TileManager
	{
		std::list<Tile> tiles;

		void parseFile( const std::string& path,
						const TextureManager& textures );

	public:
		void init( const PackageManager& packages,
				   const TextureManager& textures );

		// The returned value is thread safe
		// It will not be modified after init() has been called
		const Tile* getTile( Tile::ID id )const;

		static const std::vector<std::string> AUTO_CACHE_ID_COMPONENTS;
	};
}
