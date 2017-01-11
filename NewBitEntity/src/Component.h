#pragma once
#include "stdafx.h"

namespace nb
{
	class Entity;

	class Component
	{
	public:
		Component() = delete;
		template < class DerivedType >
		Component( DerivedType* derived )
			:type( typeid( DerivedType ) )
		{};
		Component( const Component& component ) = delete;
		Component( Component&& component ) = default;
		const std::type_index type;

		virtual void init( const Entity& entity ) = 0;
		/* Not called on World::~World() */
		virtual void destroy( const Entity& entity ) = 0;
	};
}
