#include "ItemSpawnTask.h"
using namespace std;
using namespace sf;
using namespace nb;

const float ItemSpawnTask::MIN_DISTANCE_BETWEEN_ITEMS_IN_PIXEL = 1.f * METER_TO_PIXEL;

nb::ItemSpawnTask::ItemSpawnTask( const ItemFactory * itemFactory,
								  float spawnChanceInPercentPerTry,
								  int timeBetweenTryInMilliseconds,
								  float radiusMinInPixel,
								  float radiusMaxInPixel )
	: itemFactory( itemFactory ),
	spawnChanceInPercentPerTry( spawnChanceInPercentPerTry ),
	timeBetweenTryInMilliseconds( timeBetweenTryInMilliseconds ),
	radiusMinInPixel( radiusMinInPixel ),
	radiusMaxInPixel( radiusMaxInPixel ),
	spawnChanceDistribution( 0, 100 ),
	spawnOffsetXDistribution( radiusMinInPixel, radiusMaxInPixel ),
	spawnOffsetRotationDistribution( 0.f, 360.f )
{}

void nb::ItemSpawnTask::spawnUpdate( World & world,
									 const Position & spawnFeetPosition,
									 std::mt19937 & randomNumberEngine )
{
	const auto frametimeInMilliseconds = world.getSystem<TimeSystem>()->getTimestep().asMilliseconds();
	timeSinceLastSpawnTryInMilliseconds += frametimeInMilliseconds;

	if( timeSinceLastSpawnTryInMilliseconds >= timeBetweenTryInMilliseconds )
	{
		timeSinceLastSpawnTryInMilliseconds = 0;
		if( spawnChanceDistribution( randomNumberEngine ) < spawnChanceInPercentPerTry )
			spawn( world, spawnFeetPosition, randomNumberEngine );
	}
}

void nb::ItemSpawnTask::spawn( World & world,
							   const Position & spawnFeetPosition,
							   std::mt19937& randomNumberEngine ) const
{
	// determine item spawn position
	const sf::Vector2f unrotatedOffset( spawnOffsetXDistribution( randomNumberEngine ),
										0 );
	const auto rotateInDegree = spawnOffsetRotationDistribution( randomNumberEngine );
	auto spawnOffset = rotateVector( unrotatedOffset, rotateInDegree );

	// is spawn position available?
	PhysicsSystem* physics = world.getSystem<PhysicsSystem>();

	const auto& maxSteps = 4;
	const auto& stepSize = 360.f / maxSteps;
	for( int step = 0; step < maxSteps; ++step )
	{
		Position spawnPosition( spawnFeetPosition );
		spawnPosition.xy += spawnOffset;

		b2AABB aabb;
		aabb.lowerBound.x = spawnPosition.xy.x - ( MIN_DISTANCE_BETWEEN_ITEMS_IN_PIXEL * 0.5f );
		aabb.lowerBound.y = spawnPosition.xy.y - MIN_DISTANCE_BETWEEN_ITEMS_IN_PIXEL;
		aabb.upperBound.x = spawnPosition.xy.x + ( MIN_DISTANCE_BETWEEN_ITEMS_IN_PIXEL * 0.5f );
		aabb.upperBound.y = spawnPosition.xy.y;

		if( physics->getEntitiesInAABB( aabb, spawnPosition.layer ).size() == 0 )
		{
			// spawn position is available => spawn item here
			world.addEntity( ItemManager::createItemEntity( itemFactory->create(), spawnPosition ) );
			break;
		}

		spawnOffset = rotateVector( spawnOffset, stepSize );
	}
}
