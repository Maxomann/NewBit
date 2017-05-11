#include "Item.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::Item::Item( std::string name,
				const TextureReference* texture )
	: name( move( name ) ),
	texref( move( texture ) )
{}

const std::string & nb::Item::getName() const
{
	return name;
}

const TextureReference * nb::Item::getTextureReference() const
{
	return texref;
}
