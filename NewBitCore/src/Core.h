#pragma once
#include "stdafx.h"
#include "CoreEngineManager.h"

namespace nb
{
	class Core
	{
		CoreEngineManager engines;

	public:
		void run();
	};
}
