#pragma once
#include "stdafx.h"

namespace nb
{
	class Entity;

	class WorldGenerator
	{
	public:
		// thread safe
		DLL_EXPORT virtual std::vector<Entity> generateChunk( const sf::Vector3i& chunkPosition )const = 0;
	};
}
