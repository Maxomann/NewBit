#include "DefaultItem.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::DefaultItem::DefaultItem( const std::string name, const TextureReference * texture )
	: Item( name,
			texture )
{}

void nb::DefaultItem::use( World & world, Entity * entity )
{
	return;
}
