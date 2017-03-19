#pragma once
#include "stdafx.h"

namespace nb
{
	class Entity;

	class Component
	{
		Entity* r_entity;

	public:
		DLL_EXPORT Component() = default;
		DLL_EXPORT Component( const Component& component ) = delete;
		DLL_EXPORT Component( Component&& component ) = default;
		DLL_EXPORT virtual ~Component() = default;

		DLL_EXPORT void linkToEntity( Entity* entity );
		DLL_EXPORT Entity* getEntity()const;
		DLL_EXPORT Entity* entity()const;

		virtual void init() = 0;
		/* Not called on World::~World() */
		virtual void destroy() = 0;
	};
}
