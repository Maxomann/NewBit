#pragma once
#include "stdafx.h"
#include "TextureReference.h"
#include "PackedTextureGenerationStateException.h"

namespace nb
{
	namespace tp
	{
		class PackedTexture
		{
			PackedTextureId m_id;

			bool m_isGenerated = false;

			std::vector<std::pair<TextureId, sf::Texture>> m_subTextures;

			void m_throwIfGenerated();
			void m_throwIfNotGenerated();

		public:
			PackedTexture( PackedTextureId id );
			PackedTexture( const PackedTexture& tex ) = delete;
			PackedTexture( PackedTexture&& tex ) = delete;

			PackedTextureId getId()const;

			void addTexture( TextureId textureId, const sf::Image& image );
			void addTexture( TextureId textureId, const sf::Texture& texture );

			void generate();

			sf::Texture getTexture();
			sf::Image renderAsImage()const;

			TextureReference getTextureReference( const TextureId& textureId )const;
		};
	}
}
