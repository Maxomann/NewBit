#include "MathExtensions.h"
using namespace std;
using namespace sf;

sf::Vector2f nb::rotateVector( const sf::Vector2f& vec, float angleDeg )
{
	const auto angleRad = degToRad( angleDeg );
	const auto sinVal = sin( angleRad );
	const auto cosVal = cos( angleRad );

	sf::Vector2f retVal;

	retVal.x = ( vec.x * cosVal ) - ( vec.y * sinVal );
	retVal.y = ( vec.x * sinVal ) + ( vec.y * cosVal );

	return retVal;
}
