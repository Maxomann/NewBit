#include "EntityManager.h"
using namespace std;

void nb::entity::EntityManager::executeDeleteEntities()
{
	m_entities.remove_if( [ & ]( auto& el ) {
		for ( auto it = m_toDelete.begin(); it != m_toDelete.end(); ++it )
		{
			if ( *it == &el )
			{
				m_toDelete.erase( remove( m_toDelete.begin(), m_toDelete.end(), &el ) );
				el.destroy();
				return true;
			}
		}
		return false;
	} );

	if ( m_toDelete.size() != 0 )
	{
		throw exception::EntityDoesNotExistException();
	}
}

nb::entity::Entity * nb::entity::EntityManager::createEntity( std::vector<std::unique_ptr<Component>>&& components )
{
	Entity entity;
	for ( auto& el : components )
		entity.addComponent( move( el ) );
	entity.init();

	m_entities.push_back( move( entity ) );
	return &m_entities.back();
}

void nb::entity::EntityManager::deleteEntity( Entity * entity )
{
	m_toDelete.push_back( entity );
}

DLL_EXPORT int nb::entity::EntityManager::getEntityCount() const
{
	return m_entities.size();
}