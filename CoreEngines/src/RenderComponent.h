#pragma once
#include "stdafx.h"

namespace nb
{
	class RenderComponent : public Component
	{
		int m_zValue = 0;

		std::vector<const sf::Drawable*> m_drawables;

	public:
		RenderComponent( int zValue = 0 );

		virtual void init() override;
		virtual void destroy() override;

		int getZValue()const;
		void setZValue( int zValue );

		void addDrawable( const sf::Drawable* drawable );
		void removeDrawable( const sf::Drawable* drawable );

		const std::vector<const sf::Drawable*>& getDrawingData()const;
	};
}
