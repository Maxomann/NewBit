#pragma once
#include "stdafx.h"
#include "EntityRenderer.h"

#include "TransformationComponent.h"
#include "TextureReference.h"

namespace nb
{
	class SpriteRenderer : public EntityRenderer
	{
		sf::Sprite m_sprite;
		sf::FloatRect globalBounds;

		void setSize( sf::Vector2f newSize );

		void calculateGlobalBounds();

	public:
		SpriteRenderer( const sf::Texture& texture );
		SpriteRenderer( const TextureReference& texture );

		virtual void init( const Entity* entity ) override;

		virtual const sf::FloatRect& getGlobalBounds()const override;

		virtual void draw( sf::RenderTarget& target, sf::RenderStates states )const override;

		void setTexture( const sf::Texture& texture );
		void setTexture( const TextureReference& texture );

		const sf::Sprite& getSprite()const;
	};
}
