#pragma once
#include "stdafx.h"
#include "UpdateOrder.h"

namespace nb
{
	class SystemManager;
	class EntityManager;

	class System
	{
	public:
		System() = delete;
		template < class DerivedType >
		System( DerivedType* derived, UpdateOrder updateOrder = 0 )
			: type( typeid( DerivedType ) ),
			updateOrder( updateOrder )
		{};
		System( const System& system ) = delete;
		System( System&& system ) = default;
		const std::type_index type;
		const UpdateOrder updateOrder;

		virtual void init( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
		virtual void update( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
		/* Not called on World::~World() */
		virtual void destroy( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
	};
}
