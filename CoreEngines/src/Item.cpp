#include "Item.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::Item::Item( ID id,
				std::string name,
				const TextureReference* texture )
	:id( move( id ) ),
	name( move( name ) ),
	texref( move( texture ) )
{
}

Item::ID nb::Item::getId() const
{
	return id;
}

const std::string & nb::Item::getName() const
{
	return name;
}

const TextureReference * nb::Item::getTextureReference() const
{
	return texref;
}
