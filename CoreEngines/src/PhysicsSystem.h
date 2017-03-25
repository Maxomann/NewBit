#pragma once
#include "stdafx.h"
#include "TimeSystem.h"
#include "PhysicsComponent.h"

namespace nb
{
	class PhysicsSystem : public System
	{
		b2World simulation;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;

	public:
		PhysicsSystem();

		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;
	};
}
