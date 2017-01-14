#pragma once
#include "stdafx.h"

namespace nb
{
	class TestGameState : public nb::GameState
	{
	public:
		DLL_EXPORT virtual void init( const CoreRefs& coreRefs ) override;

		DLL_EXPORT virtual void destroy( const CoreRefs& coreRefs ) override;

		DLL_EXPORT virtual bool shouldDestroy() override;
	};
}
