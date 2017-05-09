#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "sfmlExtensions.h"
#include "TileMapComponent.h"

namespace nb
{
	class ChunkSystem : public System
	{
		World* r_world;

		std::map<sf::Vector3i, std::vector<Entity*>> m_entitiesByChunk;

		void onEntityPositionChanged( const TransformationComponent*const transform,
									  const Position& oldPosition );
		void onEntityAdded( Entity* entity );
		void onEntitiesRemoved( const std::vector<Entity*>& entities );

	public:
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;

		std::vector<Entity*> getEntitiesInChunk( sf::Vector3i chunkPosition )const;

		template<class UnaryPredicate>
		std::vector<Entity*> getEntitiesInChunk_if( sf::Vector3i chunkPosition, const UnaryPredicate& pred )const
		{
			std::vector<Entity*> retVal;

			auto result = m_entitiesByChunk.find( chunkPosition );
			if( result != m_entitiesByChunk.end() )
				for( const auto& el : result->second )
				{
					if( pred( el ) )
						retVal.push_back( el );
				}
			return retVal;
		}

		void removeEntitiesInChunk( sf::Vector3i chunkPosition );

		template<class UnaryPredicate>
		void removeEntitiesInChunk_if( sf::Vector3i chunkPosition, const UnaryPredicate& pred )
		{
			for( const auto& el : m_entitiesByChunk[ chunkPosition ] )
			{
				if( pred( el ) )
					r_world->removeEntity( el );
			}
		};

		static const int CHUNK_SIZE_IN_PIXEL;

		static sf::Vector3i calculateChunkPositionForPixelPosition( const sf::Vector3i& pixelPosition );
	};
}
