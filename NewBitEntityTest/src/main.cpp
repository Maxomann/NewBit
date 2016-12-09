#include "stdafx.h"
#include "TestSystem.h"
#include "TestComponent.h"

using namespace std;
using namespace nb::entity;

SUITE( NewBitEntity )
{
	TEST( WorldTest )
	{
		World world;
		TestSystem* system = world.addSystem<TestSystem>();

		world.initSystems();

		vector<unique_ptr<Component>> vec;
		vec.push_back( make_unique<TestComponent>() );
		Entity* entity = world.createEntity( move( vec ) );
		TestComponent* component = entity->getComponent<TestComponent>();

		world.update();
		world.afterUpdate();

		CHECK( system->has_init );
		CHECK( system->has_update );
		CHECK( world.getEntityCount() == 1 );
		CHECK( component->has_init );
		CHECK( system == world.getSystem<TestSystem>() );

		world.update();
		world.deleteEntity( entity );

		CHECK( world.getEntityCount() == 1 );

		world.afterUpdate();

		CHECK( world.getEntityCount() == 0 );

		world.removeSystem<TestSystem>();
	}
}

int main()
{
	auto retVal = UnitTest::RunAllTests();
	system( "pause" );
	return retVal;
}