#pragma once
#include "stdafx.h"
#include "CoreEngineManager.h"

namespace nb
{
	class Core
	{
		CoreEngineManager m_engines;

		entity::World m_world;

	public:
		void run();
	};
}
