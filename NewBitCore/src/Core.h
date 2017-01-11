#pragma once
#include "stdafx.h"
#include "CoreEngineManager.h"
#include "GameStateManager.h"

namespace nb
{
	class Core
	{
		CoreEngineManager m_engines;
		GameStateManager m_gameStates;

		World m_world;

	public:
		void run();
	};
}
