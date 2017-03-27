#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "MathExtensions.h"
#include "id.h"

namespace nb
{
	class PhysicsComponent : public Component
	{
		b2BodyDef bodyDef;
		std::unique_ptr<b2Shape> shape;
		b2FixtureDef fixtureDef;

		bool isUpdatingToComponents = false;
		b2Body* body = nullptr;

	public:
		PhysicsComponent( b2BodyDef bodyDef,
						  std::unique_ptr<b2Shape> shape,
						  b2FixtureDef fixtureDef );

		virtual void init() override;
		virtual void destroy() override;

		void addToSimulation( b2World& simulation );
		void removeFromSimulation( b2World& simulation );

		void updateSimulationDataToComponentsIfActive();

		b2Body* getBody();
	};
}
