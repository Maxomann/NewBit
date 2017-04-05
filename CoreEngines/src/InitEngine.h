#pragma once
#include "stdafx.h"
#include "ChunkSystem.h"
#include "PhysicsSystem.h"
#include "TimeSystem.h"
#include "WorldLoadStateSystem.h"
#include "NeedsSystem.h"

namespace nb
{
	class InitEngine : public CoreEngine
	{
	public:
		virtual void init() override;

		virtual bool update() override;
	};
}
