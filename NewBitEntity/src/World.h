#pragma once
#include "stdafx.h"
#include "EntityManager.h"
#include "SystemManager.h"

namespace nb
{
	namespace entity
	{
		class World : public EntityManager, public SystemManager
		{
		public:
			DLL_EXPORT World();

			DLL_EXPORT void update();
		};
	}
}