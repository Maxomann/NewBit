#pragma once
#include "TestGameState.h"
#include "id.h"

namespace nb
{
	class TestEngine : public nb::CoreEngine
	{
	public:
		DLL_EXPORT TestEngine();

		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual bool update()override;
	};
}
