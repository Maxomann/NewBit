#pragma once
#include "stdafx.h"
#include "CoreEngineManager.h"
#include "GameStateManager.h"

namespace nb
{
	class Core
	{
		using connectFunctionSignature = void( CoreEngineManager*, GameStateManager* );

		CoreEngineManager m_engines;
		GameStateManager m_gameStates;

		void loadPluginsFromFolder( std::string pathToFolder );

	public:
		Core();

		void run();
	};
}
