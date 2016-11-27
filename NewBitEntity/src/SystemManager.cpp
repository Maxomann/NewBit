#include "SystemManager.h"

void nb::entity::SystemManager::sortSystemsByUpdateOrder()
{
	if ( !m_isSorted )
	{
		std::sort( m_systemsByUpdateOrder.begin(), m_systemsByUpdateOrder.end(), [ & ]( const System* lhs, const System* rhs ) {
			return lhs->updateOrder < rhs->updateOrder;
		} );
		m_isSorted = true;
	}
}

void nb::entity::SystemManager::updateSystems()
{
	sortSystemsByUpdateOrder();
	for ( auto& el : m_systemsByUpdateOrder )
		el->update( *this, *r_entityManager );
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