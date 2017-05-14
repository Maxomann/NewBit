#include "DefaultItemFactory.h"
#include "ResourceEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::DefaultItemFactory::DefaultItemFactory( ID id,
											NAME name,
											LABELS labels,
											const TextureReference* texture )
	: ItemFactory( id, move( name ), move( labels ) ), texture( texture )
{}

std::unique_ptr<Item> nb::DefaultItemFactory::create() const
{
	return make_unique<DefaultItem>( getName(),
									 texture );
}
