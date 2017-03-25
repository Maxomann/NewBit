#pragma once
#include "stdafx.h"

namespace nb
{
	class PhysicsComponent : public Component
	{
		b2Body* body = nullptr;

	public:
		virtual void init() override;
		virtual void destroy() override;

		void addToSimulation( b2World& simulation );
		void removeFromSimulation( b2World& simulation );
	};
}
