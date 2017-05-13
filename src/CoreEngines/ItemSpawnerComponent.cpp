#include "ItemSpawnerComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::ItemSpawnerComponent::ItemSpawnerComponent( const std::unique_ptr<ItemFactory>& itemFactory,
												float spawnChanceInPercent,
												float radiusMinInPixel,
												float radiusMaxInPixel )
	: itemFactory( itemFactory ),
	spawnChanceInPercent( spawnChanceInPercent ),
	radiusMinInPixel( radiusMinInPixel ),
	radiusMaxInPixel( radiusMaxInPixel ),
	spawnChanceDistribution( 0, 100 ),
	spawnOffsetXDistribution( radiusMinInPixel, radiusMaxInPixel ),
	spawnOffsetRotationDistribution( 0.f, 360.f )
{
	randomNumberEngine.seed( random_device() );
}

void nb::ItemSpawnerComponent::init()
{
	transform = entity()->getComponent<TransformationComponent>();
}

void nb::ItemSpawnerComponent::spawnWithChance( ResourceEngine& resources, World & world ) const
{
	if( spawnChanceDistribution( randomNumberEngine ) < spawnChanceInPercent )
		spawn( resources, world );
}

void nb::ItemSpawnerComponent::spawn( ResourceEngine& resources, World & world ) const
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
	Entity* entity;
	for( int step = 0; step < ( maxSteps - 1 ); ++step )
	{
		if( physics->getFirstEntityAtPixelPosition( spawnPosition ) == nullptr )
		{
			// spawn position is available => spawn item here
			world.addEntity( ItemManager::createItemEntity( itemFactory->create( resources ), spawnPosition ) );
			break;
		}

		spawnPosition.xy = rotateVector( spawnPosition.xy, stepSize );
	}
}
