#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "EntityDoesNotExistException.h"

namespace nb
{
	class EntityManager
	{
		std::list<Entity> m_entities;
		std::vector<Entity*> m_toDelete;

		template < class ComponentType0 >
		void addComponentsToEntity( Entity* entity )
		{
			entity->addComponent<ComponentType0>( std::make_unique<ComponentType0>() );
		}
		template < class ComponentType0, class ComponentType1, class ... ComponentTypes>
		void addComponentsToEntity( Entity* entity )
		{
			entity->addComponent<ComponentType0>( std::make_unique<ComponentType0>() );
			addComponentsToEntity<ComponentType1, ComponentTypes...>( entity );
		}

	protected:
		void executeRemoveEntities();

	public:
		DLL_EXPORT Entity* addEntity( Entity&& entity );
		template< class ... ComponentTypes >
		Entity* createEntity()
		{
			Entity entity;
			addComponentsToEntity<ComponentTypes...>( &entity );

			return addEntity( move( entity ) );
		};

		DLL_EXPORT void removeEntity( Entity* entity );

		DLL_EXPORT int getEntityCount()const;

		Signal<void, Entity*> s_onEntityAdded;
		Signal<void, const std::vector<Entity*>&> s_onEntitiesRemoved;
	};
}
