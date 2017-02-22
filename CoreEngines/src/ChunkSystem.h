#pragma once
#include "stdafx.h"

namespace nb
{
	class ChunkSystem : public System
	{
		World* r_world;

		std::map<sf::Vector3i, std::vector<Entity*>> m_loadedChunks;

		void generateChunk( sf::Vector3i chunkPosition );
		void removeChunk( sf::Vector3i chunkPosition );

		void onEntityPositionChanged();
		void onEntityAdded( Entity* entity );
		void onEntitiesRemoved( const std::vector<Entity*>& entities );

	public:
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;

		std::vector<Entity*> getEntitiesInChunk( sf::Vector3i chunkPosition );

		void ensureChunkLoadedForChunkPosition( sf::Vector3i chunkPosition );
		void ensureChunkLoadedForPixelPosition( sf::Vector3i pixelPosition );

		static const int CHUNK_SIZE_IN_PIXEL;
	};
}
