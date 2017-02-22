#pragma once
#include "stdafx.h"

namespace nb
{
	class Entity;

	class Component
	{
		Entity* r_entity;

	public:
		Component() = default;
		Component( const Component& component ) = delete;
		Component( Component&& component ) = default;

		DLL_EXPORT void linkToEntity( Entity* entity );
		DLL_EXPORT Entity* getEntity()const;

		virtual void init() = 0;
		/* Not called on World::~World() */
		virtual void destroy() = 0;
	};
}
