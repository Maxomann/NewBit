#pragma once
#include "stdafx.h"
#include "CameraComponent.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"

namespace nb
{
	class RenderSystem : public System
	{
		using DrawingData = std::vector<std::pair<const sf::View*, std::vector<const sf::Drawable*>>>;

		std::vector<Entity*> m_camerasForDrawing;
		std::vector<Entity*> m_entitiesToDraw;

		std::vector<std::unique_ptr<sf::Drawable>> debugDrawingData;

		DrawingData m_drawingData;
		bool m_drawingDataIsValid = false;

		void onEntityAdded( Entity* entity );
		void onEntitiesRemoved( const std::vector<Entity*>& entities );

		void generateDrawingData();
	public:

		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;

		void setCamerasForDrawing( std::vector<Entity*> cameras );
		const std::vector<Entity*>& getCamerasForDrawing()const;

		const DrawingData& getCurrentDrawingData();

		Signal<void( const std::vector<Entity*>& )> s_camerasForDrawingChanged;
		Signal<void( std::vector<std::unique_ptr<sf::Drawable>>&, int )> s_collectDebugDrawingData;
	};
}
