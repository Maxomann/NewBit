#pragma once
#include "stdafx.h"
#include "CoreRef.h"

namespace nb
{
	class CoreEngineManager;
	class GameStateManager;
	class World;

	class GameState : public CoreRefContainer
	{
	public:
		DLL_EXPORT GameState() = default;
		DLL_EXPORT GameState( const GameState& ) = delete;
		DLL_EXPORT GameState( GameState&& ) = delete;
		DLL_EXPORT virtual ~GameState() = default;

		DLL_EXPORT virtual void init() = 0;

		DLL_EXPORT virtual void update() = 0;

		DLL_EXPORT virtual void destroy() = 0;

		DLL_EXPORT virtual bool shouldDestroy() = 0;
	};

	/*
	virtual void init() override;

	virtual void update() override;

	virtual void destroy() override;

	virtual bool shouldDestroy() override;
	*/
}
