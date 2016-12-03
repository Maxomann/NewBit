#pragma once
#include "stdafx.h"
#include "id.h"

namespace nb
{
	namespace tp
	{
		class TextureReference
		{
			TextureId m_id;
			sf::Texture& m_textureRef;
			sf::Vector2i m_positionOnTexture;

			sf::IntRect m_textureRect;

		public:
			TextureReference( TextureId id, sf::Texture& textureRef, sf::Vector2i positionOnTexture );
			TextureReference( const TextureReference& tex ) = default;
			TextureReference( TextureReference&& tex ) = default;

			TextureId getId()const;

			void setTextureRect( sf::IntRect textureRect );
			sf::IntRect getTextureRect()const;

			void applyToSprite( sf::Sprite& sprite )const;
		};
	}
}