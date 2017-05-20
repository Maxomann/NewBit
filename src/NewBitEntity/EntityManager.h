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

	protected:
		void executeRemoveEntities();

	public:
		DLL_EXPORT Entity* addEntity( Entity&& entity );
		DLL_EXPORT void addEntities( std::vector<Entity>&& entities );

		DLL_EXPORT void removeEntity( Entity* entity );
		// void removeEntities( std::vector<Entity*> entity );

		DLL_EXPORT std::vector<Entity> removeEntities_move( std::vector<Entity*> entities );

		DLL_EXPORT int getEntityCount()const;

		Signal<void( Entity* )> s_onEntityAdded;
		Signal<void( const std::vector<Entity*>& )> s_onEntitiesRemoved;
		Signal<void( unsigned int )> s_onEntityCountChanged;
	};
}
