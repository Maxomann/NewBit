#pragma once
#include "stdafx.h"
#include "SpriteComponent.h"
#include "CameraComponent.h"
#include "TransformationComponent.h"

namespace nb
{
	class RenderSystem : public System
	{
		using DrawingData = std::vector<std::pair<const sf::View*, std::vector<const sf::Drawable*>>>;

		std::vector<Entity*> m_camerasForDrawing;
		std::vector<Entity*> m_entitiesToDraw;

		DrawingData m_drawingData;

		void onEntityAdded( Entity* entity );
		void onEntitiesRemoved( const std::vector<Entity*>& entities );
	public:

		virtual void init( World& world ) override;
		virtual void update( World& world ) override;
		virtual void destroy( World& world ) override;

		void setCamerasForDrawing( std::vector<Entity*> cameras );

		const DrawingData& getCurrentDrawingData()const;
	};
}
