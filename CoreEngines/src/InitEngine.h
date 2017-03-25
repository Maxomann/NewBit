#pragma once
#include "stdafx.h"
#include "ChunkSystem.h"
#include "PhysicsSystem.h"
#include "TimeSystem.h"

namespace nb
{
	class InitEngine : public CoreEngine
	{
	public:
		virtual void init() override;

		virtual bool update() override;
	};
}
