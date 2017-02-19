#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	struct CoreRef
	{
		const CoreEngineManager& engines;
		GameStateManager& gameStates;
		World& world;

		CoreRef( const CoreEngineManager& engines,
				 GameStateManager& gameStates,
				 World& world )
			: engines( engines ),
			gameStates( gameStates ),
			world( world )
		{};
	};
}
