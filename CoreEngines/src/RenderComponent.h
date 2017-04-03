#pragma once
#include "stdafx.h"

namespace nb
{
	class RenderComponent : public Component
	{
		int m_zValue = 0;

		std::vector<const sf::Drawable*> m_drawables;
		std::map<const sf::Drawable*, const sf::FloatRect*> globalBounds;
		const sf::FloatRect defaultRect = { 0, 0, 0, 0 };

	public:
		RenderComponent( int zValue = 0 );

		virtual void init() override;
		virtual void destroy() override;

		int getZValue()const;
		void setZValue( int zValue );

		void addDrawable( const sf::Drawable* drawable, const sf::FloatRect* globalBoundsPtr );
		void removeDrawable( const sf::Drawable* drawable );

		const sf::FloatRect& getGlobalBounds()const;

		const std::vector<const sf::Drawable*>& getDrawingData()const;
	};
}
