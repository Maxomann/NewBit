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

		std::mt19937 randomNumberEngine;
		std::uniform_real_distribution<float> spawnChanceDistribution;
		std::uniform_real_distribution<float> spawnOffsetXDistribution;
		std::uniform_real_distribution<float> spawnOffsetRotationDistribution;

		const std::unique_ptr<ItemFactory>& itemFactory;
		float spawnChanceInPercent;
		float radiusMinInPixel;
		float radiusMaxInPixel;

	public:
		ItemSpawnerComponent( const std::unique_ptr<ItemFactory>& itemFactory,
							  float spawnChanceInPercent,
							  float radiusMinInPixel,
							  float radiusMaxInPixel );

		virtual void init() override;

		void spawnWithChance( ResourceEngine& resources, World& world )const;
		void spawn( ResourceEngine& resources, World& world )const;
	};
}
