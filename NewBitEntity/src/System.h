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
			System()
				: type( typeid( DerivedType ) )
			{};
			System( const System& system ) = delete;
			System( System&& system ) = default;
			const std::type_index type;

			virtual void init( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
			virtual void update( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
			virtual void destroy( const SystemManager& systemManager, const EntityManager& entityManager ) = 0;
		};
	}
}