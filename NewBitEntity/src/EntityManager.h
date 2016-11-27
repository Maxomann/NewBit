#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "EntityDoesNotExistException.h"

namespace nb
{
	namespace entity
	{
		class EntityManager
		{
			std::list<Entity> m_entities;
			std::vector<Entity*> m_toDelete;

		protected:
			void executeDeleteEntities();

		public:
			DLL_EXPORT Entity* createEntity( std::vector<std::unique_ptr<Component>>&& components );
			DLL_EXPORT void deleteEntity( Entity* entity );

			DLL_EXPORT int getEntityCount()const;
		};
	}
}