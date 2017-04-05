#pragma once
#include "stdafx.h"
#include "NeedsComponent.h"
#include "ComponentCache.h"
#include "TimeSystem.h"

namespace nb
{
	class NeedsSystem : public System
	{
		TimeSystem* timeSystem;

		ComponentCache<NeedsComponent> needsComponentCache;

	public:
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;
	};
}
