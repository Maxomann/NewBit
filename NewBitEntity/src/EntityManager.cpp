#include "EntityManager.h"
using namespace std;
using namespace nb;

void nb::EntityManager::executeRemoveEntities()
{
	if (m_toDelete.size() > 0)
		s_onEntitiesRemoved.call( m_toDelete );

	m_entities.remove_if( [&]( auto& el ) {
		for (auto it = m_toDelete.begin(); it != m_toDelete.end(); ++it)
		{
			if (*it == &el)
			{
				m_toDelete.erase( remove( m_toDelete.begin(), m_toDelete.end(), &el ) );
				el.destroy();
				return true;
			}
		}
		return false;
	} );

	if (m_toDelete.size() != 0)
	{
		throw exception::EntityDoesNotExistException();
	}
}

Entity * nb::EntityManager::addEntity( Entity&& entity )
{
	m_entities.push_back( std::move( entity ) );

	Entity* en = &m_entities.back();
	en->init();
	s_onEntityAdded.call( en );
	return en;
}

void nb::EntityManager::removeEntity( Entity * entity )
{
	m_toDelete.push_back( entity );
}

int nb::EntityManager::getEntityCount() const
{
	return m_entities.size();
}
