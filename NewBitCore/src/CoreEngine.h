#pragma once
#include "stdafx.h"
#include "CoreRef.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	class CoreEngine
	{
	public:
		DLL_EXPORT virtual ~CoreEngine() = default;

		DLL_EXPORT virtual void init( const CoreRef& coreRefs ) = 0;

		// return false to terminate process
		DLL_EXPORT virtual bool update( const CoreRef& coreRefs ) = 0;
	};
}
