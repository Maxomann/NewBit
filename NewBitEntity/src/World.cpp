#include "World.h"
using namespace std;

nb::entity::World::World()
	: EntityManager(), SystemManager( *( ( EntityManager* )this ) )
{}

void nb::entity::World::update()
{
	updateSystems();
}

void nb::entity::World::afterUpdate()
{
	executeDeleteEntities();
}