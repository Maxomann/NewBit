#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "MathExtensions.h"

namespace nb
{
	class PhysicsComponent : public Component
	{
		bool isUpdatingToComponents = false;
		b2Body* body = nullptr;

	public:

		virtual void init() override;
		virtual void destroy() override;

		void addToSimulation( b2World& simulation );
		void removeFromSimulation( b2World& simulation );

		void updateSimulationDataToComponentsIfActive();

		b2Body* getBody();
	};
}
