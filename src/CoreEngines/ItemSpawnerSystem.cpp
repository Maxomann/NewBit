#include "ItemSpawnerSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ItemSpawnerSystem::init()
{
	componentCache.connectToWorld( world() );
}

void nb::ItemSpawnerSystem::update()
{
	/*for( auto& el : componentCache.get() )
		el->spawnWithChance()*/
}

void nb::ItemSpawnerSystem::destroy()
{}
