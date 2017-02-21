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

	public:
		DLL_EXPORT System( UpdateOrder updateOrder = 0 );
		DLL_EXPORT System( const System& system ) = delete;
		DLL_EXPORT System( System&& system ) = default;

		virtual void init( World& world ) = 0;
		virtual void update( World& world ) = 0;
		/* Not called on World::~World() */
		virtual void destroy( World& world ) = 0;

		DLL_EXPORT virtual UpdateOrder getUpdateOrder()const;
	};
}
