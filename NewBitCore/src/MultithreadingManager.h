#pragma once
#include "stdafx.h"

namespace nb
{
	class MultithreadingManager
	{
	public:
		DLL_EXPORT void tick();

		ThreadSafeSignal<void> s_executeNextTick;
	};
}
