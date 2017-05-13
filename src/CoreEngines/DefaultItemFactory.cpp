#include "DefaultItemFactory.h"
#include "ResourceEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::DefaultItemFactory::DefaultItemFactory( ID id,
											NAME name,
											LABELS labels,
											GlobalId textureId )
	: ItemFactory( id, move( name ), move( labels ) ), textureId( textureId )
{}

std::unique_ptr<Item> nb::DefaultItemFactory::create( const ResourceEngine & resources ) const
{
	return make_unique<DefaultItem>( getName(),
									 resources.textures.getTextureReference( textureId ) );
}
