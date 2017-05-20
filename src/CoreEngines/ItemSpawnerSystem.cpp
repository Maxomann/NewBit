#include "ItemSpawnerSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ItemSpawnerSystem::init()
{
	randomNumberEngine.seed( random_device()( ) );

	itemCache.connectToWorld( world() );
	spawnerCache.connectToWorld( world() );
}

void nb::ItemSpawnerSystem::update()
{
	for( auto& el : itemCache.get() )
		if( el->isEmpty() )
			world()->removeEntity( el->entity() );

	for( auto& el : spawnerCache.get() )
		el->spawnUpdate( *world(), randomNumberEngine );
}

void nb::ItemSpawnerSystem::destroy()
{}
