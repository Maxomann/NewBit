#include "Position.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::Position::Position( sf::Vector2f xy, int layer )
	:xy( move( xy ) ),
	layer( layer )
{}

nb::Position::Position( float x, float y, int layer )
	: Position( {x,y}, layer )
{}

sf::Vector3i nb::Position::asPixelPosition()const
{
	return sf::Vector3i( static_cast<int>( xy.x ),
						 static_cast<int>( xy.y ),
						 layer );
}

bool nb::Position::operator==( const Position & other )
{
	return ( this->xy == other.xy && this->layer == other.layer );
}

bool nb::Position::operator!=( const Position & other )
{
	return !operator==( other );
}
