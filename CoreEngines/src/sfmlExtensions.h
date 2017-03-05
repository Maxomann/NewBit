#pragma once
#include "stdafx.h"

namespace sf
{
	template<typename T>
	bool operator<( const sf::Vector3<T>& lhs, const sf::Vector3<T>& rhs )
	{
		if (lhs.z < rhs.z)
			return true;
		if (rhs.z < lhs.z)
			return false;

		// a1==b1: continue with element 2
		if (lhs.y < rhs.y)
			return true;
		if (rhs.y < lhs.y)
			return false;

		// a2 == b2: continue with element 3
		if (lhs.x < rhs.x)
			return true;
		return false; // early out
	}
}
