#pragma once
#include "stdafx.h"
#include "PhysicsComponent.h"

namespace nb
{
	class PhysicsAABBCallback : public b2QueryCallback
	{
	public:
		std::vector<b2Body*> foundBodies;

		virtual bool ReportFixture( b2Fixture* fixture ) override;
	};

	class PhysicsContactListener : public b2ContactListener
	{
		void BeginContact( b2Contact* contact ) {
			PhysicsComponent* userDataA = static_cast<PhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
			PhysicsComponent* userDataB = static_cast<PhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

			if (userDataA)
				userDataA->beginContact( userDataB );

			if (userDataB)
				userDataB->beginContact( userDataA );
		}

		void EndContact( b2Contact* contact ) {
			PhysicsComponent* userDataA = static_cast<PhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
			PhysicsComponent* userDataB = static_cast<PhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

			if (userDataA)
				userDataA->endContact( userDataB );

			if (userDataB)
				userDataB->endContact( userDataA );
		}
	};
}
