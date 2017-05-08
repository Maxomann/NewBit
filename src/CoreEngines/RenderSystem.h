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
		std::vector<RenderComponent*> renderComponentsInWorld;

		std::vector<std::unique_ptr<sf::Drawable>> debugDrawingData;

		void onEntityAdded( Entity* entity );
		void onEntitiesRemoved( const std::vector<Entity*>& entities );

	public:

		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;

		const std::vector<RenderComponent*>& getRenderComponentsInWorld()const;

		const std::vector<std::unique_ptr<sf::Drawable>>& getDebugDrawingDataForLayer( int layer );

		Signal<void( const std::vector<Entity*>& )> s_camerasForDrawingChanged;
		Signal<void( std::vector<std::unique_ptr<sf::Drawable>>&, int )> s_collectDebugDrawingData;
	};
}
