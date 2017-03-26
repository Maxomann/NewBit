#include "PhysicsSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::PhysicsSystem::PhysicsSystem()
	: simulation( b2Vec2( 0, 0 ) ),
	debugDraw( make_unique<PhysicsDebugDraw>() )
{
	debugDraw->SetFlags( b2Draw::e_shapeBit );
	simulation.SetDebugDraw( debugDraw.get() );
}

void nb::PhysicsSystem::init()
{
	world()->s_onEntityAdded.connect( [&]( Entity* entity ) {
		auto physics = entity->getComponent_try<PhysicsComponent>();
		if (physics)
			physics->addToSimulation( simulation );
	} );
	world()->s_onEntitiesRemoved.connect( [&]( const std::vector<Entity*>& vec ) {
		for (const auto& entity : vec)
		{
			auto physics = entity->getComponent_try<PhysicsComponent>();
			if (physics)
				physics->removeFromSimulation( simulation );
		}
	} );
	system<RenderSystem>()->s_collectDebugDrawingData.connect( [&]( auto& vec ) {
		if (drawDebugLayer)
		{
			debugDraw->setDrawContainer( vec );
			simulation.DrawDebugData();
		}
	} );
}

void nb::PhysicsSystem::update()
{
	auto& frameTime = system<TimeSystem>()->getFrameTime();
	simulation.Step( frameTime.asMilliseconds(), velocityIterations, positionIterations );
	simulation.DrawDebugData();

	if (sf::Keyboard::isKeyPressed( Keyboard::J ))
	{
		/* test */
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set( 0, 0 );
		bodyDef.linearDamping = 0.0005f;
		bodyDef.angularDamping = 0.0005f;

		auto body = simulation.CreateBody( &bodyDef );

		b2PolygonShape shape;
		shape.SetAsBox( 0.5f, 0.5f );

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture( &fixtureDef );

		body->ApplyForce( b2Vec2( 0, -0.001f ), b2Vec2( 0, 0 ), true );
	}
}

void nb::PhysicsSystem::destroy()
{
}
