#include "Item.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::Item::Item( const std::string name,
				const TextureReference* texture,
				std::string useActionName,
				bool isUsePossible )
	: name( move( name ) ),
	texref( move( texture ) ),
	usePossible( isUsePossible ),
	useActionName( useActionName )
{}

nb::Item::Item( const std::string name, const TextureReference * texture )
	:Item( move( name ),
		   move( texture ),
		   "NO_USE",
		   false )
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
