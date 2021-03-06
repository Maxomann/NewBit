#pragma once
#include "stdafx.h"

namespace nb
{
	template<class T>
	constexpr T PI = T( 3.1415926535897932385 );

	template< class T >
	T radToDeg( const T& rad )
	{
		return (rad * static_cast<T>(180)) / PI<T>;
	}

	template< class T >
	T degToRad( const T& deg )
	{
		return (deg * PI<T>) / static_cast<T>(180);
	}
}
