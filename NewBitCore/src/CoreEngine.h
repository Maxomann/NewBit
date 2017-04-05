#pragma once
#include "stdafx.h"
#include "CoreRef.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	class CoreEngine : public CoreRefContainer
	{
	public:
		DLL_EXPORT virtual ~CoreEngine() = default;

		DLL_EXPORT virtual void init() = 0;

		// return false to terminate process
		DLL_EXPORT virtual bool update() = 0;
	};

	/*
		virtual void init() override;
		virtual bool update() override;
	*/
}
