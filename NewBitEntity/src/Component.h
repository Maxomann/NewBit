#pragma once
#include "stdafx.h"

namespace nb
{
	class Entity;

	class Component
	{
	public:
		Component() = default;
		Component( const Component& component ) = delete;
		Component( Component&& component ) = default;

		virtual void init( const Entity& entity ) = 0;
		/* Not called on World::~World() */
		virtual void destroy( const Entity& entity ) = 0;
	};
}
