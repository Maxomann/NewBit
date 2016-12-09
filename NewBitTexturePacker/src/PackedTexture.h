#pragma once
#include "stdafx.h"
#include "TextureReference.h"
#include "PackedTextureGenerationStateException.h"
#include "PackedTextureDuplicateException.h"
#include "TextureTooLargeException.h"

namespace nb
{
	namespace tp
	{
		struct PackingElement
		{
			TextureId id;
			sf::Texture* texture;
			sf::IntRect rect;
			unsigned int destinationTextureId;
		};

		class PackedTexture
		{
			PackedTextureId m_id;

			bool m_isGenerated = false;

			std::vector<std::pair<TextureId, sf::Texture>> m_subTextures;

			const unsigned int m_maximumSize = 0;
			std::unordered_map<TextureId, TextureReference> m_generatedTextureReferences;
			std::deque<sf::RenderTexture> m_generatedTextures;

			void m_throwIfGenerated();
			void m_throwIfNotGenerated();

		public:
			PackedTexture( PackedTextureId id, unsigned int maximumSize );
			PackedTexture( const PackedTexture& tex ) = delete;
			PackedTexture( PackedTexture&& tex ) = delete;

			PackedTextureId getId()const;

			void addTexture( TextureId textureId, const sf::Image& image );
			void addTexture( TextureId textureId, const sf::Texture& texture );

			void generate();

			std::vector<sf::Image> renderAsImages()const;

			TextureReference getTextureReference( const TextureId& textureId )const;

			static void packingAlgorithm( std::vector<PackingElement>& elements, const unsigned int maximumTextureSize );
		};
	}
}
