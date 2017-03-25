#include "PhysicsSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::PhysicsSystem::PhysicsSystem()
	: simulation( b2Vec2( 0, 0 ) )
{
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

	/* test */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set( 0, 0 );

	auto body = simulation.CreateBody( &bodyDef );

	b2PolygonShape shape;
	shape.SetAsBox( 10, 10, b2Vec2( 0, 5 ), 0.f );

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture( &fixtureDef );
}

void nb::PhysicsSystem::update()
{
	auto& frameTime = system<TimeSystem>()->getFrameTime();
	cout << frameTime.asMilliseconds() << endl;
	simulation.Step( frameTime.asMilliseconds(), velocityIterations, positionIterations );
	simulation.DrawDebugData();
}

void nb::PhysicsSystem::destroy()
{
}
