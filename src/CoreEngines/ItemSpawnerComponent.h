#pragma once
#include "stdafx.h"
#include "ItemSpawnTask.h"

namespace nb
{
	class ItemSpawnerComponent : public Component
	{
		TransformationComponent* transform;

		std::vector<ItemSpawnTask> spawnTasks;

	public:
		ItemSpawnerComponent( std::vector<ItemSpawnTask> spawnTasks );

		virtual void init() override;

		void spawnUpdate( World& world, std::mt19937& randomNumberEngine );
	};
}
