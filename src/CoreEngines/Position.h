#pragma once
#include "stdafx.h"

namespace nb
{
	struct Position
	{
	public:
		sf::Vector2f xy = {0.f, 0.f};
		int layer = 0;

		Position() = default;
		Position( sf::Vector2f xy, int layer );
		Position( float x,
				  float y,
				  int layer );
		Position( sf::Vector3i position );
		Position( const Position& ) = default;
		Position( Position&& ) = default;

		sf::Vector3i asPixelPosition()const;

		bool operator==( const Position& other );
		bool operator!=( const Position& other );

		Position& operator=( const Position& other ) = default;
		Position& operator=( Position&& other ) = default;
	};
}
