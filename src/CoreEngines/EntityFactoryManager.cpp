#include "EntityFactoryManager.h"
using namespace std;
using namespace nb;

void nb::EntityFactoryManager::init()
{
	addFactory( make_unique<TreeFactory>() );
	addFactory( make_unique<WallFactory>() );
	addFactory( make_unique<ItemEntityWoodFactory>() );
}
