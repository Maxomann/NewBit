#pragma once
#include "stdafx.h"

namespace nb
{
	class TextureReference
	{
		const GlobalId m_id;
		const sf::Texture& m_texture;
		const sf::IntRect m_defaultTextureRect;

	public:
		TextureReference( GlobalId id,
						  const sf::Texture& texture,
						  const sf::IntRect defaultTextureRect );
		TextureReference( const TextureReference& rhs ) = default;
		TextureReference( TextureReference&& rhs ) = default;

		const sf::Texture& getTexture()const;
		const sf::IntRect& getDefaultTextureRect()const;

		TextureReference& operator=( const TextureReference& rhs ) = default;
		TextureReference& operator=( TextureReference&& rhs ) = default;
	};
}
