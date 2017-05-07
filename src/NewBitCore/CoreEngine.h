#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;

	class CoreEngine
	{
	public:
		DLL_EXPORT virtual ~CoreEngine() = default;

		DLL_EXPORT virtual void init( const CoreEngineManager& coreEngines ) = 0;

		// return false to terminate process
		DLL_EXPORT virtual bool update() = 0;
	};

	/*
		virtual void init( const CoreEngineManager& coreEngines ) override;

		virtual bool update() override;
	*/
}
