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
			const sf::Texture& m_textureRef;
			sf::Vector2i m_positionOnTexture;

			sf::IntRect m_textureRect;

		public:
			DLL_EXPORT TextureReference(TextureId id,
				const sf::Texture& textureRef,
				sf::Vector2i positionOnTexture,
				sf::IntRect defaultTextureRect );
			DLL_EXPORT TextureReference(const TextureReference& tex) = default;
			DLL_EXPORT TextureReference(TextureReference&& tex) = default;

			DLL_EXPORT TextureId getId()const;
			DLL_EXPORT const sf::Texture& getTexturePtr()const;
			DLL_EXPORT sf::Vector2i getPositionOnTexture()const;

			DLL_EXPORT void setTextureRect(sf::IntRect textureRect);
			DLL_EXPORT sf::IntRect getTextureRect()const;

			DLL_EXPORT void applyToSprite(sf::Sprite& sprite)const;
		};
	}
}