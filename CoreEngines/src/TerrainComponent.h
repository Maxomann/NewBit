#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TextureReference.h"
#include "sfmlExtensions.h"

namespace nb
{
	class TerrainComponent : public Component, public sf::Drawable
	{
		std::vector<std::vector<TextureReference>> tiles;

		std::map<const sf::Texture*, std::vector<sf::Vertex>> vertexArrays;

		void generate();

	public:
		TerrainComponent( TextureReference defaultTile );
		TerrainComponent( std::vector<std::vector<TextureReference>> tiles );

		virtual void init() override;
		virtual void destroy() override;

		void setTiles( std::map<sf::Vector2i, TextureReference> tileTexturesByPosition );

		virtual void draw( sf::RenderTarget& target, sf::RenderStates states )const override;

		static const int TILE_SIZE_IN_PIXEL;
		static const int TERRAIN_SIZE_IN_PIXEL;
		static const int TILES_PER_TERRAIN;
	};
}
