#pragma once
#include "stdafx.h"

namespace nb
{
	namespace entity
	{
		class SystemManager;
		class EntityManager;

		class System
		{
		public:
			System() = delete;
			template < class DerivedType >
			System( DerivedType* derived )
				: type( typeid( DerivedType ) )
			{};
			System( const System& system ) = delete;
			System( System&& system ) = default;
			const std::type_index type = typeid( System );

			virtual void init( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
			virtual void update( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
			/* Not called on World::~World() */
			virtual void destroy( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
		};
	}
}