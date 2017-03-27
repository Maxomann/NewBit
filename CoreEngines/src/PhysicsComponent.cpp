#include "PhysicsComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::PhysicsComponent::init()
{
	auto transform = component<TransformationComponent>();

	transform->s_positionXYChanged.connect( [&]( const auto& comp, const auto& oldPosition ) {
		auto newPositionXY = comp->getPositionXY();
		body->GetPosition().Set( newPositionXY.x, newPositionXY.y );
	} );

	transform->s_rotationChanged.connect( [&]( const auto& comp, const auto& oldRotation ) {
		auto newRotation = comp->getRotation();
		body->GetTransform().q.Set( degToRad( newRotation ) );
	} );
}

void nb::PhysicsComponent::destroy()
{
}

void nb::PhysicsComponent::addToSimulation( b2World & simulation )
{
	auto transform = component<TransformationComponent>();
	auto position = transform->getPositionXY();
	auto rotation = transform->getRotation();

	/* init */

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set( position.x, position.y );
	bodyDef.angle = degToRad( rotation );

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

void nb::PhysicsComponent::updateSimulationDataToComponentsIfActive()
{
	isUpdatingToComponents = true;

	if (body->IsActive())
	{
		/* DO IMPORTANT UPDATING HERE */
		// ...
	}
}

b2Body * nb::PhysicsComponent::getBody()
{
	return body;
}
