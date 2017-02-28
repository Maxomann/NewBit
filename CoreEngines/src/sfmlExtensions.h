#pragma once
#include "stdafx.h"

namespace sf
{
	template<typename T>
	bool operator<( const sf::Vector3<T>& lhs, const sf::Vector3<T>& rhs )
	{
		if (lhs.z < rhs.z)
			return true;
		else if (lhs.y < rhs.y)
			return true;
		else if (lhs.x < rhs.x)
			return true;
		else
			return false;
	}
}
