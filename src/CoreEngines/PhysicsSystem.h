#pragma once
#include "stdafx.h"
#include "TimeSystem.h"
#include "PhysicsComponent.h"
#include "RenderSystem.h"
#include "PhysicsDebugDraw.h"
#include "PhysicsSystemCallbacks.h"

namespace nb
{
	class PhysicsSystem : public System
	{
		b2Vec2 defaultGravity = b2Vec2( 0, 0 );
		std::map<int, b2World> simulation;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		std::vector<Entity*> entitiesWithPhysicsComponentInWorld;

		PhysicsContactListener contactListener;

		bool drawDebugLayer = false;
		std::unique_ptr<PhysicsDebugDraw> debugDraw;

		b2World& getSimulationForLayer( int layer );
		void checkSimulationLayerForRemoval( int layer );

	public:
		PhysicsSystem();

		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;

		void setDebugDrawEnabled( bool enabled );
		bool isDebugDrawEnabled()const;

		Entity* getFirstEntityAtPixelPosition( const sf::Vector3i& position );
	};
}
