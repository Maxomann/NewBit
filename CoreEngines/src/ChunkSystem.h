#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "SpriteComponent.h"
#include "sfmlExtensions.h"

namespace nb
{
	class ChunkSystem : public System
	{
		World* r_world;

		std::unordered_map<sf::Vector3i, std::vector<Entity*>> m_entitiesByChunk;

		void onEntityPositionChanged( const TransformationComponent*const transform, sf::Vector3i oldPosition );
		void onEntityAdded( Entity* entity );
		void onEntitiesRemoved( const std::vector<Entity*>& entities );

	public:
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;

		std::vector<Entity*> getEntitiesInChunk( sf::Vector3i chunkPosition )const;

		void removeEntitiesInChunk( sf::Vector3i chunkPosition );

		static const int CHUNK_SIZE_IN_PIXEL;

		static sf::Vector3i calculateChunkPositionForPixelPosition( const sf::Vector3i& pixelPosition );
	};
}
