#pragma once
#include "stdafx.h"
#include "CoreEngineManager.h"
#include "GameStateManager.h"
#include "CoreRef.h"
#include "MultithreadingManager.h"

namespace nb
{
	class Core
	{
		CoreEngineManager m_engines;
		GameStateManager m_gameStates;

		World m_world;

		MultithreadingManager m_multithreadingManager;

	public:
		void run();
	};
}
