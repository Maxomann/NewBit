#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "MathExtensions.h"
#include "id.h"

namespace nb
{
	class PhysicsComponent : public Component
	{
		const b2BodyDef defaultBodyDef;
		const std::unique_ptr<b2Shape> shape;
		const b2FixtureDef defaultFixtureDef;

		bool isUpdatingToComponents = false;
		b2Body* body = nullptr;

		bool transparent;

	public:
		PhysicsComponent( b2BodyDef defaultBodyDef,
						  std::unique_ptr<b2Shape> shape,
						  b2FixtureDef defaultFixtureDef,
						  bool transparent = false );

		virtual void init() override;

		void addToSimulation( b2World& simulation );
		void removeFromSimulation( b2World& simulation );

		void updateSimulationDataToComponents();

		b2Body* getBody();

		// should only be called by PhysicsContactListener
		void beginContact( PhysicsComponent* other );
		void endContact( PhysicsComponent* other );

		bool isTransparent()const;

		// parameter is the other component
		Signal<void( const PhysicsComponent* )> s_beginCollision;
		// parameter is the other component
		Signal<void( const PhysicsComponent* )> s_endCollision;
	};
}
