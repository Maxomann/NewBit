#pragma once
#include "stdafx.h"
#include "NeedsComponent.h"

namespace nb
{
	class NeedsSystem : public System
	{
	public:
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;
	};
}
