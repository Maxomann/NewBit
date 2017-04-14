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
		[[deprecated]] DLL_EXPORT Entity* getEntity()const;
		DLL_EXPORT Entity* entity()const;
		template<class T>
		T* component()const
		{
			return entity()->getComponent<T>();
		};

		virtual void init() = 0;
	};

	/*
		virtual void init() override;
	*/
}
