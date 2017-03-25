#include "PhysicsComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::PhysicsComponent::init()
{
}

void nb::PhysicsComponent::destroy()
{
}

void nb::PhysicsComponent::addToSimulation( b2World & simulation )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set( 0, 0 );

	body = simulation.CreateBody( &bodyDef );

	b2PolygonShape shape;
	shape.SetAsBox( 10, 10, b2Vec2( 0, 5 ), 0.f );

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture( &fixtureDef );
}

void nb::PhysicsComponent::removeFromSimulation( b2World & simulation )
{
	if (body)
	{
		simulation.DestroyBody( body );
		body = nullptr;
	}
}
