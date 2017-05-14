#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "ItemFactory.h"
#include "ItemManager.h"
#include "MathExtensions.h"

#include "PhysicsSystem.h"

namespace nb
{
	class ItemSpawnerComponent : public Component
	{
		TransformationComponent* transform;

		mutable std::mt19937 randomNumberEngine;
		std::uniform_real_distribution<float> spawnChanceDistribution;
		std::uniform_real_distribution<float> spawnOffsetXDistribution;
		std::uniform_real_distribution<float> spawnOffsetRotationDistribution;

		const ItemFactory* itemFactory;
		const float spawnChanceInPercentPerTry;
		const int timeBetweenTryInMilliseconds;
		const float radiusMinInPixel;
		const float radiusMaxInPixel;

		int timeSinceLastSpawnTryInMilliseconds = 0;

	public:
		ItemSpawnerComponent( const ItemFactory* itemFactory,
							  float spawnChanceInPercentPerTry,
							  int timeBetweenTryInMilliseconds,
							  float radiusMinInPixel,
							  float radiusMaxInPixel );

		virtual void init() override;

		void spawnUpdate( World& world );
		void spawn( World& world )const;
	};
}
