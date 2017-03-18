#pragma once
#include "stdafx.h"
#include "id.h"

namespace nb
{
	namespace tp
	{
		class TextureReference
		{
			const TextureId m_id;
			const sf::Texture& m_textureRef;
			const sf::Vector2i m_positionOnTexture;

			const sf::IntRect m_defaultTextureRectInDefaultCoordinates;

		public:
			DLL_EXPORT TextureReference( TextureId id,
										 const sf::Texture& textureRef,
										 sf::Vector2i positionOnTexture,
										 sf::IntRect defaultTextureRectInDefaultCoordinates );
			DLL_EXPORT TextureReference( const TextureReference& tex ) = default;
			DLL_EXPORT TextureReference( TextureReference&& tex ) = default;

			DLL_EXPORT TextureId getId()const;
			DLL_EXPORT const sf::Texture& getTexturePtr()const;
			DLL_EXPORT sf::Vector2i getPositionOnTexture()const;

			DLL_EXPORT sf::IntRect tranformTextureRectToReferenceCoordinates( sf::IntRect textureRect )const;
			DLL_EXPORT const sf::IntRect& getDefaultTextureRect()const;

			// applies texture and defaultTextureRect
			DLL_EXPORT void applyToSprite( sf::Sprite& sprite )const;
		};
	}
}
