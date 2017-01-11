#include "World.h"
using namespace std;

nb::World::World()
	: EntityManager(), SystemManager( *( ( EntityManager* )this ) )
{}

void nb::World::update()
{
	updateSystems();
	executeDeleteEntities();
}
