#include "ItemSpawnerComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::ItemSpawnerComponent::ItemSpawnerComponent( const ItemFactory* itemFactory,
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
{
	randomNumberEngine.seed( random_device()( ) );
}

void nb::ItemSpawnerComponent::init()
{
	transform = entity()->getComponent<TransformationComponent>();
}

void nb::ItemSpawnerComponent::spawnUpdate( World & world )
{
	const auto frametimeInMilliseconds = world.getSystem<TimeSystem>()->getTimestep().asMilliseconds();
	timeSinceLastSpawnTryInMilliseconds += frametimeInMilliseconds;

	if( timeSinceLastSpawnTryInMilliseconds >= timeBetweenTryInMilliseconds )
	{
		timeSinceLastSpawnTryInMilliseconds = 0;
		if( spawnChanceDistribution( randomNumberEngine ) < spawnChanceInPercentPerTry )
			spawn( world );
	}
}

void nb::ItemSpawnerComponent::spawn( World & world ) const
{
	// determine item spawn position
	Position spawnPosition( transform->getPosition() );

	const sf::Vector2f unrotatedOffset( spawnOffsetXDistribution( randomNumberEngine ),
										0 );
	const auto rotateInDegree = spawnOffsetRotationDistribution( randomNumberEngine );
	auto spawnOffset = rotateVector( unrotatedOffset, rotateInDegree );

	spawnPosition.xy += spawnOffset;

	// is spawn position available?
	PhysicsSystem* physics = world.getSystem<PhysicsSystem>();

	const auto& maxSteps = 4;
	const auto& stepSize = 360.f / maxSteps;
	for( int step = 0; step < ( maxSteps - 1 ); ++step )
	{
		if( physics->getFirstEntityAtPixelPosition( spawnPosition ) == nullptr )
		{
			// spawn position is available => spawn item here
			world.addEntity( ItemManager::createItemEntity( itemFactory->create(), spawnPosition ) );
			break;
		}

		spawnPosition.xy = rotateVector( spawnPosition.xy, stepSize );
	}
}
