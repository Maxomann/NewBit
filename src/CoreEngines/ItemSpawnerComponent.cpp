#include "ItemSpawnerComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::ItemSpawnerComponent::ItemSpawnerComponent( std::vector<ItemSpawnTask> spawnTasks )
	: spawnTasks( move( spawnTasks ) )
{}

void nb::ItemSpawnerComponent::init()
{
	transform = entity()->getComponent<TransformationComponent>();
}

void nb::ItemSpawnerComponent::spawnUpdate( World& world, std::mt19937& randomNumberEngine )
{
	for( auto& el : spawnTasks )
		el.spawnUpdate( world, transform->getPosition(), randomNumberEngine );
}
