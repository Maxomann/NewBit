#include "EntityFactoryManager.h"
using namespace std;
using namespace nb;

void nb::EntityFactoryManager::init()
{
	addFactory( make_unique<TreeFactory>() );
	addFactory( make_unique<ItemWoodFactory>() );
}

void nb::EntityFactoryManager::addFactory( FACTORY_PTR factory )
{
	factories.emplace( make_pair( factory->getId(), move( factory ) ) );
}

const EntityFactoryManager::FACTORY_PTR & nb::EntityFactoryManager::getFactoryById( EntityFactory::ID id ) const
{
	return factories.at( id );
}

const EntityFactoryManager::FACTORIES & nb::EntityFactoryManager::getAllFactories() const
{
	return factories;
}
