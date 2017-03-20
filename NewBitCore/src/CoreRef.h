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
		[[deprecated]]const CoreRef* getCore()
		{
			return r_core;
		};
		const CoreRef* core()
		{
			return r_core;
		};

		template<class T>
		T* engine()
		{
			return r_core->engines.getEngine<T>();
		}

		const CoreEngineManager& engines()const
		{
			return r_core->engines;
		}

		GameStateManager& gameStates()const
		{
			return r_core->gameStates;
		}

		World& world()const
		{
			return r_core->world;
		}
	};
}
