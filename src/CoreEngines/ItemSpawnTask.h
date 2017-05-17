#pragma once
#include "stdafx.h"

#include "TransformationComponent.h"
#include "ItemFactory.h"
#include "ItemManager.h"
#include "MathExtensions.h"

#include "PhysicsSystem.h"

namespace nb
{
	class ItemSpawnTask
	{
		const ItemFactory* itemFactory;
		const float spawnChanceInPercentPerTry;
		const int timeBetweenTryInMilliseconds;
		const float radiusMinInPixel;
		const float radiusMaxInPixel;

		int timeSinceLastSpawnTryInMilliseconds = 0;

		std::uniform_real_distribution<float> spawnChanceDistribution;
		std::uniform_real_distribution<float> spawnOffsetXDistribution;
		std::uniform_real_distribution<float> spawnOffsetRotationDistribution;

		static const float MIN_DISTANCE_BETWEEN_ITEMS_IN_PIXEL;

	public:
		ItemSpawnTask( const ItemFactory* itemFactory,
					   float spawnChanceInPercentPerTry,
					   int timeBetweenTryInMilliseconds,
					   float radiusMinInPixel,
					   float radiusMaxInPixel );

		void spawnUpdate( World& world,
						  const Position& spawnCenterPosition,
						  std::mt19937& randomNumberEngine );

		void spawn( World& world,
					const Position& spawnCenterPosition,
					std::mt19937& randomNumberEngine )const;
	};
}
