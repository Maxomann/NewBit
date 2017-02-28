#pragma once
#include "stdafx.h"
#include "ChunkSystem.h"

namespace nb
{
	class InitEngine : public CoreEngine
	{
	public:
		virtual void init() override;

		virtual bool update() override;
	};
}
