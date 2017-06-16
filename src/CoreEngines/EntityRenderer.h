#pragma once
#include "stdafx.h"

namespace nb
{
	class EntityRenderer : public sf::Drawable
	{
	public:
		virtual ~EntityRenderer() = default;

		virtual void init( const Entity* entity ) = 0;

		virtual const sf::FloatRect& getGlobalBounds()const = 0;

		virtual void draw( sf::RenderTarget& target, sf::RenderStates states )const override = 0;
	};

	/*
	virtual void init( const Entity* entity ) override;

	virtual const sf::FloatRect& getGlobalBounds()const override;

	virtual void draw( sf::RenderTarget& target, sf::RenderStates states )const override;
	*/
}
