#pragma once
#include "stdafx.h"

namespace nb
{
	class InitEngine : public CoreEngine
	{
	public:
		virtual void init() override;

		virtual bool update() override;
	};
}
