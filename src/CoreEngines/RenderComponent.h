#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

#include "EntityRenderer.h"

namespace nb
{
	class RenderComponent : public Component
	{
		const TransformationComponent* transformComponent;
		int m_zValue = 0;

		std::vector<std::unique_ptr<EntityRenderer>> renderers;
		std::vector<const sf::Drawable*> drawables;
		const sf::FloatRect defaultRect = {0, 0, 0, 0};

		bool isInit = false;

	public:
		RenderComponent( int zValue = 0 );
		RenderComponent( std::vector<std::unique_ptr<EntityRenderer>> renderers,
						 int zValue = 0 );
		RenderComponent( const RenderComponent& ) = delete;

		virtual void init() override;

		sf::Vector2i getSortPositionXY()const;
		const int getDrawingLayer()const;

		const int& getZValue()const;
		void setZValue( int zValue );

		void addRenderer( std::unique_ptr<EntityRenderer> renderer );

		const sf::FloatRect& getGlobalBounds()const;

		const std::vector<const sf::Drawable*>& getDrawingData()const;
	};
}
