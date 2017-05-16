#include "ItemSpawnerSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ItemSpawnerSystem::init()
{
	randomNumberEngine.seed( random_device()( ) );

	componentCache.connectToWorld( world() );
}

void nb::ItemSpawnerSystem::update()
{
	for( auto& el : componentCache.get() )
		el->spawnUpdate( *world(), randomNumberEngine );
}

void nb::ItemSpawnerSystem::destroy()
{}
