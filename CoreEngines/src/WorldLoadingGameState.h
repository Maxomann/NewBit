#pragma once
#include "stdafx.h"

namespace nb
{
	class WorldLoadingGameState : public GameState
	{
	public:
		virtual void init() override;

		virtual void destroy() override;

		virtual bool shouldDestroy() override;

		static const int CHUNK_LOADING_RADIUS;
	};
}
