#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TextureReference.h"
#include "sfmlExtensions.h"
#include "Tile.h"

namespace nb
{
	class TileMapComponent : public Component, public sf::Drawable
	{
		std::vector<std::vector<const Tile*>> tiles;

		mutable std::mutex vertexArraysMutex;
		std::map<const sf::Texture*, std::vector<sf::Vertex>> vertexArrays;
		sf::FloatRect globalBounds;
		void calculateGlobalBounds();

		std::future<void> generationFuture;
		void generate();
		void generate_internal();

	public:
		TileMapComponent( const Tile* defaultTile );
		TileMapComponent( const Tile* defaultTile,
						  std::map<sf::Vector2i, const Tile*> tileTexturesByPosition );
		TileMapComponent( std::vector<std::vector<const Tile*>> tiles );
		~TileMapComponent();

		virtual void init() override;
		virtual void destroy() override;

		void setTiles( std::map<sf::Vector2i, const Tile*> tilesByPosition );
		const Tile* getTile( sf::Vector2i relativePosition )const;

		virtual void draw( sf::RenderTarget& target, sf::RenderStates states )const override;

		sf::Vector2i calculateRelativeTilePosition( sf::Vector3i absoluteTilePosition );

		static const int TILE_SIZE_IN_PIXEL;
		static const int TERRAIN_SIZE_IN_PIXEL;
		static const int TILES_PER_TERRAIN;
	};
}
