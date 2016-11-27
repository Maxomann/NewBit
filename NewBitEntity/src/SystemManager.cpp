#include "SystemManager.h"

void nb::entity::SystemManager::updateSystems()
{
	for ( auto& el : m_systems )
		el.second->update( *this, *r_entityManager );
}

nb::entity::SystemManager::SystemManager( EntityManager & entityManager )
	:r_entityManager( &entityManager )
{}

void nb::entity::SystemManager::initSystems()
{
	if ( m_isInit )
	{
		throw exception::SystemManagerAlreadyInitializedException();
	}
	for ( auto& el : m_systems )
	{
		el.second->init( *this, *r_entityManager );
	}
	m_isInit = true;
}