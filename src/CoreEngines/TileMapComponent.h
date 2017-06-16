#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TextureReference.h"
#include "sfmlExtensions.h"
#include "Tile.h"

namespace nb
{
	class TileMapComponent : public Component
	{
	public:
		using TileData = std::vector<std::vector<const Tile*>>;

	private:
		TileData tiles;

	public:
		TileMapComponent( const Tile* defaultTile );
		TileMapComponent( const Tile* defaultTile,
						  std::map<sf::Vector2i, const Tile*> tileTexturesByPosition );
		TileMapComponent( std::vector<std::vector<const Tile*>> tiles );

		virtual void init() override;

		void setTiles( std::map<sf::Vector2i, const Tile*> tilesByPosition );
		const Tile* getTile( sf::Vector2i relativePosition )const;
		const TileData& getTileData()const;

		sf::Vector2i calculateRelativeTilePosition( sf::Vector3i absoluteTilePosition );

		Signal<void( const TileData& data )> s_tilesChanged;

		static const int TILE_SIZE_IN_PIXEL;
		static const int TERRAIN_SIZE_IN_PIXEL;
		static const int TILES_PER_TERRAIN;
	};
}
