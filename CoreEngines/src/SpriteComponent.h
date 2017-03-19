#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "TextureReference.h"
#include "RenderComponent.h"

namespace nb
{
	class SpriteComponent : public nb::Component
	{
		sf::Sprite m_sprite;

		void setSize( sf::Vector2u size );
	public:
		SpriteComponent( const sf::Texture& texture );
		SpriteComponent( const TextureReference& texture );

		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual void destroy()override;

		void setTexture( const sf::Texture& texture );
		void setTexture( const TextureReference& texture );

		const sf::Sprite& getSprite()const;
	};
}
