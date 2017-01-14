#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	struct CoreRefs
	{
		const CoreEngineManager& engines;
		GameStateManager& gameStates;
		World& world;

		CoreRefs( const CoreEngineManager& engines,
				  GameStateManager& gameStates,
				  World& world )
			: engines( engines ),
			gameStates( gameStates ),
			world( world )
		{};
	};
}
