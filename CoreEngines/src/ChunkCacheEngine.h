#pragma once
#include "stdafx.h"
#include "sfmlExtensions.h"

namespace nb
{
	class ChunkCacheEngine : public CoreEngine
	{
		std::map<sf::Vector3i, std::vector<Entity>> cache;

	public:
		virtual void init() override;
		virtual bool update() override;

		void setCache( std::vector<Entity>&& entities, sf::Vector3i chunkPosition );

		// cache is removed after getCache()
		std::vector<Entity> getCache( sf::Vector3i chunkPosition );

		bool hasCache( sf::Vector3i chunkPosition )const;
	};
}
