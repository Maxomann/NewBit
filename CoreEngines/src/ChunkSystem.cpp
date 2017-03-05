#include "ChunkSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

const int ChunkSystem::CHUNK_SIZE_IN_PIXEL = 640;

void nb::ChunkSystem::onEntityPositionChanged( const TransformationComponent*const transform,
											   sf::Vector3i oldPosition )
{
	auto entity = transform->getEntity();
	auto newPosition = transform->getPosition();
	auto newChunkPosition = calculateChunkPositionForPixelPosition( newPosition );
	auto oldChunkPosition = calculateChunkPositionForPixelPosition( oldPosition );
	if (newChunkPosition != oldChunkPosition)
	{
		auto& newChunk = m_entitiesByChunk[newChunkPosition];
		auto& oldChunk = m_entitiesByChunk[oldChunkPosition];

		oldChunk.erase( remove( oldChunk.begin(), oldChunk.end(), entity ) );
		newChunk.push_back( entity );
	}
}

void nb::ChunkSystem::onEntityAdded( Entity * entity )
{
	auto transform = entity->getComponent_try<TransformationComponent>();
	if (transform)
	{
		transform->s_positionChanged.connect_mem_fn_auto( &ChunkSystem::onEntityPositionChanged, *this );
		auto chunkPositon = calculateChunkPositionForPixelPosition( transform->getPosition() );
		auto& chunk = m_entitiesByChunk[chunkPositon];
		chunk.push_back( entity );
	}
}

void nb::ChunkSystem::onEntitiesRemoved( const std::vector<Entity*>& entities )
{
	std::map<sf::Vector3i, std::vector<Entity*>> toRemoveByChunk;

	for (const auto& el : entities)
	{
		auto transform = el->getComponent_try<TransformationComponent>();
		if (transform)
		{
			auto chunkPosition = calculateChunkPositionForPixelPosition( transform->getPosition() );
			toRemoveByChunk[chunkPosition].push_back( el );
		}
	}

	for (const auto& el : toRemoveByChunk)
	{
		auto& chunk = m_entitiesByChunk[el.first];
		chunk.erase( remove_if( chunk.begin(), chunk.end(), [&]( const Entity* inner ) -> bool {
			return (find( el.second.begin(), el.second.end(), inner ) != el.second.end());
		} ), chunk.end() );
	}
}

void nb::ChunkSystem::init()
{
	r_world = getWorld();

	r_world->s_onEntityAdded.connect_mem_fn_auto( &ChunkSystem::onEntityAdded, *this );
	r_world->s_onEntitiesRemoved.connect_mem_fn_auto( &ChunkSystem::onEntitiesRemoved, *this );
}

void nb::ChunkSystem::update()
{
}

void nb::ChunkSystem::destroy()
{
}

std::vector<Entity*> nb::ChunkSystem::getEntitiesInChunk( sf::Vector3i chunkPosition ) const
{
	auto result = m_entitiesByChunk.find( chunkPosition );
	if (result != m_entitiesByChunk.end())
	{
		return result->second;
	}
	else
	{
		return vector<Entity*>();
	}
}

void nb::ChunkSystem::removeEntitiesInChunk( sf::Vector3i chunkPosition )
{
	for (const auto& el : m_entitiesByChunk[chunkPosition])
		r_world->removeEntity( el );
}

sf::Vector3i nb::ChunkSystem::calculateChunkPositionForPixelPosition( const sf::Vector3i & pixelPosition )
{
	auto x = pixelPosition.x / CHUNK_SIZE_IN_PIXEL;
	auto y = pixelPosition.y / CHUNK_SIZE_IN_PIXEL;

	if (pixelPosition.x < 0)
		x -= 1;

	if (pixelPosition.y < 0)
		y -= 1;

	return Vector3i( x, y, pixelPosition.z );
}
