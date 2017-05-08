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
		virtual void PreSolve( b2Contact* contact, const b2Manifold* oldManifold )override
		{
			PhysicsComponent* userDataA = static_cast<PhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
			PhysicsComponent* userDataB = static_cast<PhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

			if (userDataA->isTransparent())
				contact->SetEnabled( false );
			if (userDataB->isTransparent())
				contact->SetEnabled( false );
		}

		virtual void BeginContact( b2Contact* contact )override {
			PhysicsComponent* userDataA = static_cast<PhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
			PhysicsComponent* userDataB = static_cast<PhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

			if (userDataA)
				userDataA->beginContact( userDataB );

			if (userDataB)
				userDataB->beginContact( userDataA );
		}

		virtual void EndContact( b2Contact* contact )override {
			PhysicsComponent* userDataA = static_cast<PhysicsComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
			PhysicsComponent* userDataB = static_cast<PhysicsComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());

			if (userDataA)
				userDataA->endContact( userDataB );

			if (userDataB)
				userDataB->endContact( userDataA );
		}
	};
}
