#pragma once
#include "stdafx.h"
#include "UpdateOrder.h"

namespace nb
{
	class SystemManager;
	class EntityManager;
	class World;

	class System
	{
		const UpdateOrder m_updateOrder;

		World* r_world;

	public:
		DLL_EXPORT System( UpdateOrder updateOrder = 0 );
		DLL_EXPORT System( const System& system ) = delete;
		DLL_EXPORT System( System&& system ) = default;
		DLL_EXPORT virtual ~System() = default;

		DLL_EXPORT void linkToWorld( World* world );
		DLL_EXPORT World* getWorld()const;
		DLL_EXPORT World* world()const;

		virtual void init() = 0;
		virtual void update() = 0;
		/* Not called on World::~World() */
		virtual void destroy() = 0;

		DLL_EXPORT virtual UpdateOrder getUpdateOrder()const;
	};
}
