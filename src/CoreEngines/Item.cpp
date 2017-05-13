#include "Item.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::Item::Item( std::string name,
				const TextureReference* texture,
				bool usePossible,
				std::string useActionName )
	: name( move( name ) ),
	texref( move( texture ) ),
	usePossible( usePossible ),
	useActionName( useActionName )
{}

const std::string & nb::Item::getName() const
{
	return name;
}

const TextureReference * nb::Item::getTextureReference() const
{
	return texref;
}

bool nb::Item::canBeUsed() const
{
	return usePossible;
}

const std::string & nb::Item::getUseActionName() const
{
	return useActionName;
}
