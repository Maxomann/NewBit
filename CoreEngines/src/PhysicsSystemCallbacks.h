#pragma once
#include "stdafx.h"

namespace nb
{
	class PhysicsAABBCallback : public b2QueryCallback
	{
	public:
		std::vector<b2Body*> foundBodies;

		virtual bool ReportFixture( b2Fixture* fixture ) override;
	};
}
