#include "PhysicsSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

b2World & nb::PhysicsSystem::getSimulationForLayer( int layer )
{
	auto emplaceRetVal = simulation.try_emplace( layer, defaultGravity );
	auto& sim = emplaceRetVal.first->second;
	return sim;
}

void nb::PhysicsSystem::checkSimulationLayerForRemoval( int layer )
{
	if (simulation.at( layer ).GetBodyCount() <= 0)
		simulation.erase( layer );
}

nb::PhysicsSystem::PhysicsSystem()
	: debugDraw( make_unique<PhysicsDebugDraw>() )
{
	debugDraw->SetFlags( b2Draw::e_shapeBit );
}

void nb::PhysicsSystem::init()
{
	world()->s_onEntityAdded.connect( [&]( Entity* entity ) {
		auto transform = entity->getComponent<TransformationComponent>();
		auto physics = entity->getComponent_try<PhysicsComponent>();
		if (physics)
		{
			auto entityLayer = transform->getLayer();
			physics->addToSimulation( getSimulationForLayer( entityLayer ) );
			entitiesWithPhysicsComponentInWorld.push_back( entity );

			transform->s_layerChanged.connect( [&, physics]( const TransformationComponent* comp,
															 int oldLayer ) {
				physics->removeFromSimulation( getSimulationForLayer( oldLayer ) );
				checkSimulationLayerForRemoval( oldLayer );
				physics->addToSimulation( getSimulationForLayer( comp->getLayer() ) );
			} );
		}
	} );
	world()->s_onEntitiesRemoved.connect( [&]( const std::vector<Entity*>& vec ) {
		for (const auto& entity : vec)
		{
			auto physics = entity->getComponent_try<PhysicsComponent>();
			if (physics)
			{
				auto entityLayer = entity->getComponent<TransformationComponent>()->getLayer();
				physics->removeFromSimulation( getSimulationForLayer( entityLayer ) );
				checkSimulationLayerForRemoval( entityLayer );
			}
		}
		entitiesWithPhysicsComponentInWorld.erase( remove_if( entitiesWithPhysicsComponentInWorld.begin(),
															  entitiesWithPhysicsComponentInWorld.end(),
															  [&]( const Entity* el ) {
			return any_of( vec.begin(), vec.end(), [&]( const Entity* el2 ) {
				return el == el2;
			} );
		} ), entitiesWithPhysicsComponentInWorld.end() );
	} );
	system<RenderSystem>()->s_collectDebugDrawingData.connect( [&]( auto& vec, int layer ) {
		if (drawDebugLayer)
		{
			debugDraw->setDrawContainer( vec );
			auto& sim = getSimulationForLayer( layer );
			sim.SetDebugDraw( debugDraw.get() );
			sim.DrawDebugData();
		}
	} );
}

void nb::PhysicsSystem::update()
{
	auto& frameTime = system<TimeSystem>()->getFrameTime();
	for (auto& sim : simulation)
		sim.second.Step( frameTime.asMilliseconds(), velocityIterations, positionIterations );

	for (auto& el : entitiesWithPhysicsComponentInWorld)
		el->getComponent<PhysicsComponent>()->updateSimulationDataToComponentsIfActive();

	if (sf::Keyboard::isKeyPressed( Keyboard::J ))
	{
		/* test */
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set( 0, 0 );
		bodyDef.linearDamping = 0.0005f;
		bodyDef.angularDamping = 0.0005f;

		auto body = getSimulationForLayer( 0 ).CreateBody( &bodyDef );

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
