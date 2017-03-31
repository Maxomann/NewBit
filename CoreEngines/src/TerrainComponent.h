#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TextureReference.h"
#include "sfmlExtensions.h"
#include "Tile.h"

namespace nb
{
	class TerrainComponent : public Component, public sf::Drawable
	{
		std::vector<std::vector<const Tile*>> tiles;

		std::map<const sf::Texture*, std::vector<sf::Vertex>> vertexArrays;

		std::future<void> generationFuture;
		void generate();
		void generate_internal();

	public:
		TerrainComponent( const Tile* defaultTile );
		TerrainComponent( const Tile* defaultTile,
						  std::map<sf::Vector2i, const Tile*> tileTexturesByPosition );
		TerrainComponent( std::vector<std::vector<const Tile*>> tiles );
		~TerrainComponent();

		virtual void init() override;
		virtual void destroy() override;

		void setTiles( std::map<sf::Vector2i, const Tile*> tilesByPosition );

		virtual void draw( sf::RenderTarget& target, sf::RenderStates states )const override;

		static const int TILE_SIZE_IN_PIXEL;
		static const int TERRAIN_SIZE_IN_PIXEL;
		static const int TILES_PER_TERRAIN;
	};
}
