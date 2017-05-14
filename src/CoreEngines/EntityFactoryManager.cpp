#include "EntityFactoryManager.h"
using namespace std;
using namespace nb;

void nb::EntityFactoryManager::init( const PackageManager& packages,
									 const TextureManager& textures,
									 const ItemManager& items )
{
	addFactory( make_unique<TreeFactory>( textures, items ) );
	addFactory( make_unique<WallFactory>( textures ) );
}
