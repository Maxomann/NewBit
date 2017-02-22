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

	class CoreRefContainer
	{
		const CoreRef* r_core;

	public:
		void linkToCore( const CoreRef* core )
		{
			r_core = core;
		};
		const CoreRef* getCore()
		{
			return r_core;
		};
	};
}
