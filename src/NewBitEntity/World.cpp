#include "World.h"
using namespace std;

nb::World::World()
	: EntityManager(), SystemManager( *this )
{}

void nb::World::update()
{
	updateSystems();
	executeRemoveEntities();
}
