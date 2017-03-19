#pragma once
#include "stdafx.h"
#include "EntityManager.h"
#include "SystemManager.h"

namespace nb
{
	class World : public EntityManager, public SystemManager
	{
	public:
		DLL_EXPORT World();
		World( const World& world ) = delete;
		// deleted, since nb::System stores a reference to the world and for performance reasons
		World( World&& world ) = delete;

		DLL_EXPORT void update();
	};
}
