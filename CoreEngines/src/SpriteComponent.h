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
		sf::FloatRect globalBounds;

		void setSize( sf::Vector2f newSize );

		void calculateGlobalBounds();

	public:
		SpriteComponent() = default;
		SpriteComponent( const sf::Texture& texture );
		SpriteComponent( const TextureReference& texture );

		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual void destroy()override;

		void setTexture( const sf::Texture& texture );
		void setTexture( const TextureReference& texture );

		const sf::Sprite& getSprite()const;
	};
}
