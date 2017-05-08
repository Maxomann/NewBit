#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

namespace nb
{
	class RenderComponent : public Component
	{
		const TransformationComponent* transformComponent;
		int m_zValue = 0;

		std::vector<const sf::Drawable*> m_drawables;
		std::map<const sf::Drawable*, const sf::FloatRect*> globalBounds;
		const sf::FloatRect defaultRect = { 0, 0, 0, 0 };

	public:
		RenderComponent( int zValue = 0 );

		virtual void init() override;

		const sf::Vector2i& getSortPositionXY()const;
		const int getDrawingLayer()const;

		const int& getZValue()const;
		void setZValue( int zValue );

		void addDrawable( const sf::Drawable* drawable, const sf::FloatRect* globalBoundsPtr );
		void removeDrawable( const sf::Drawable* drawable );

		const sf::FloatRect& getGlobalBounds()const;

		const std::vector<const sf::Drawable*>& getDrawingData()const;
	};
}
