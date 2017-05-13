#include "DefaultItem.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::DefaultItem::DefaultItem( std::string name, const TextureReference * texture )
	: Item( name,
			texture,
			false,
			"NO_USE" )
{}

bool nb::DefaultItem::use( World & world, Entity * entity )
{
	return false;
}
