#include "PhysicsComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::PhysicsComponent::PhysicsComponent( b2BodyDef bodyDef,
										std::unique_ptr<b2Shape> shape,
										b2FixtureDef fixtureDef )
	:bodyDef( move( bodyDef ) ),
	shape( move( shape ) ),
	fixtureDef( move( fixtureDef ) )
{
}

void nb::PhysicsComponent::init()
{
	auto transform = component<TransformationComponent>();

	transform->s_positionXYChanged.connect( [&]( const auto& comp, const auto& oldPosition ) {
		if (!isUpdatingToComponents)
		{
			auto newPositionXY = comp->getPositionXY();
			body->SetTransform( b2Vec2( static_cast<float>(newPositionXY.x)*PIXEL_TO_METER,
										static_cast<float>(newPositionXY.y)*PIXEL_TO_METER ),
								body->GetAngle() );
		}
	} );

	transform->s_rotationChanged.connect( [&]( const auto& comp, const auto& oldRotation ) {
		if (!isUpdatingToComponents)
		{
			auto newRotation = comp->getRotation();
			body->SetTransform( body->GetPosition(),
								degToRad( newRotation ) );
		}
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
	bodyDef.position.Set( position.x*PIXEL_TO_METER,
						  position.y*PIXEL_TO_METER );
	bodyDef.angle = degToRad( rotation );

	body = simulation.CreateBody( &bodyDef );
	// store a ptr to this Component in UserData
	body->SetUserData( this );

	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape.get();

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

void nb::PhysicsComponent::updateSimulationDataToComponents()
{
	isUpdatingToComponents = true;

	auto transform = component<TransformationComponent>();

	auto position = body->GetPosition();
	transform->setPositionXY( Vector2i( position.x*METER_TO_PIXEL,
										position.y*METER_TO_PIXEL ) );
	transform->setRotation( radToDeg( body->GetAngle() ) );

	isUpdatingToComponents = false;
}

b2Body * nb::PhysicsComponent::getBody()
{
	return body;
}

void nb::PhysicsComponent::beginContact( PhysicsComponent * other )
{
	s_beginCollision.call( other );
}

void nb::PhysicsComponent::endContact( PhysicsComponent * other )
{
	s_endCollision.call( other );
}

bool nb::PhysicsComponent::isTransparent() const
{
	return true;
}
