#include "World.h"
using namespace std;

void nb::entity::World::update()
{
	updateSystems();
}

void nb::entity::World::afterUpdate()
{
	executeDeleteEntities();
}