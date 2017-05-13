#pragma once
#include "stdafx.h"
#include "ItemSpawnerComponent.h"
#include "ComponentCache.h"

namespace nb
{
	class ItemSpawnerSystem : public System
	{
		ComponentCache<ItemSpawnerComponent> componentCache;

	public:
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;
	};
}
