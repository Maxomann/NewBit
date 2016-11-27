#pragma once
#include "stdafx.h"
#include "typedefs.h"
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
			Entity* createEntity( std::vector<std::unique_ptr<Component>>& components );
			void deleteEntity( Entity* entity );
		};
	}
}