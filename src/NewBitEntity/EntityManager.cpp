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
				m_toDelete.erase( remove( m_toDelete.begin(), m_toDelete.end(), &el ), m_toDelete.end() );
				el.outsideConnections.clear();
				return true;
			}
		}
		return false;
	} );

	if (m_toDelete.size() != 0)
	{
		throw exception::EntityDoesNotExistException();
	}

	s_onEntityCountChanged.call( getEntityCount() );
}

Entity * nb::EntityManager::addEntity( Entity&& entity )
{
	m_entities.push_back( std::move( entity ) );

	Entity* en = &m_entities.back();
	if (!en->isInit())
		en->init();
	s_onEntityAdded.call( en );
	s_onEntityCountChanged.call( getEntityCount() );
	return en;
}

void nb::EntityManager::addEntities( std::vector<Entity>&& entities )
{
	while (entities.size() > 0)
	{
		addEntity( move( entities.back() ) );
		entities.pop_back();
	}
}

void nb::EntityManager::removeEntity( Entity * entity )
{
	m_toDelete.push_back( entity );
}

std::vector<Entity> nb::EntityManager::removeEntities_move( std::vector<Entity*> entities )
{
	std::vector<Entity> retVal;

	if (entities.size() > 0)
		s_onEntitiesRemoved.call( entities );

	m_entities.remove_if( [&]( auto& el ) {
		for (auto it = entities.begin(); it != entities.end(); ++it)
		{
			if (*it == &el)
			{
				entities.erase( remove( entities.begin(), entities.end(), &el ), entities.end() );
				el.outsideConnections.clear();
				retVal.push_back( move( el ) );
				return true;
			}
		}
		return false;
	} );

	if (entities.size() != 0)
		throw exception::EntityDoesNotExistException();

	s_onEntityCountChanged.call( getEntityCount() );

	return retVal;
}

int nb::EntityManager::getEntityCount() const
{
	return m_entities.size();
}
