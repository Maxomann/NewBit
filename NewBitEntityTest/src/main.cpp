#include "stdafx.h"
#include "TestSystem.h"
#include "TestComponent.h"

using namespace std;
using namespace nb;

int main()
{
	World world;
	TestSystem* system = world.addSystem<TestSystem>();

	world.initSystems();

	Entity createThisEntity;
	createThisEntity.addComponent( make_unique<TestComponent>() );

	Entity* entity = world.addEntity( move( createThisEntity ) );
	TestComponent* component = entity->getComponent<TestComponent>();

	world.update();

	CHECK( system->has_init );
	CHECK( system->has_update );
	CHECK( world.getEntityCount() == 1 );
	CHECK( component->has_init );
	CHECK( system == world.getSystem<TestSystem>() );

	world.update();
	world.removeEntity( entity );

	CHECK( world.getEntityCount() == 1 );

	world.update();

	CHECK( world.getEntityCount() == 0 );

	world.removeSystem<TestSystem>();

	std::system( "pause" );
}
