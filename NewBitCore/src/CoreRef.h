#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;
	class MultithreadingManager;

	struct CoreRef
	{
		const CoreEngineManager& engines;
		GameStateManager& gameStates;
		World& world;
		MultithreadingManager& multithreading;

		CoreRef( const CoreEngineManager& engines,
				 GameStateManager& gameStates,
				 World& world,
				 MultithreadingManager& multithreading )
			: engines( engines ),
			gameStates( gameStates ),
			world( world ),
			multithreading( multithreading )
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
