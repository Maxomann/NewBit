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

	class EngineRefContainer
	{
		const CoreEngineManager* enginesRef;
	public:
		void linkToEngines( const CoreEngineManager& engines )
		{
			this->enginesRef = &engines;
		}

		template<class T>
		T* engine()const
		{
			return r_core->engines.getEngine<T>();
		}

		const CoreEngineManager& engines()const
		{
			return *enginesRef;
		}
	};

	class GameStateRefContainer
	{
		GameStateManager* gameStatesRef;

	public:
		void linkToGameStates( GameStateManager& gameStates )
		{
			this->gameStatesRef = &gameStates;
		}

		GameStateManager& gameStates()const
		{
			return *gameStatesRef;
		}
	};

	class WorldRefContainer
	{
		World* worldRef;

	public:
		void linkToWorld( World& world )
		{
			this->worldRef = &world;
		}

		World& world()const
		{
			return *worldRef;
		}
	};

	class CoreRefContainer :
		public EngineRefContainer,
		public GameStateRefContainer,
		public WorldRefContainer
	{
		const CoreRef* r_core;

	public:
		void linkToCore( const CoreRef* core )
		{
			r_core = core;
			linkToEngines( core->engines );
			linkToGameStates( core->gameStates );
			linkToWorld( core->world );
		};
		[[deprecated]]const CoreRef* getCore()
		{
			return r_core;
		};
		const CoreRef* core()
		{
			return r_core;
		};
	};
}
