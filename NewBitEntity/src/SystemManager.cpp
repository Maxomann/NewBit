#include "SystemManager.h"

nb::SystemManager::SystemManager( World& world )
	: r_world( &world )
{}

void nb::SystemManager::sortSystemsByUpdateOrder()
{
	if (!m_isSorted)
	{
		std::sort( m_systemsByUpdateOrder.begin(), m_systemsByUpdateOrder.end(), [&]( const System* lhs, const System* rhs ) {
			return lhs->getUpdateOrder() < rhs->getUpdateOrder();
		} );
		m_isSorted = true;
	}
}

void nb::SystemManager::updateSystems()
{
	sortSystemsByUpdateOrder();
	for (auto& el : m_systemsByUpdateOrder)
		el->update( *r_world );
}

void nb::SystemManager::initSystems()
{
	if (m_isInit)
	{
		throw exception::SystemManagerAlreadyInitializedException();
	}
	for (auto& el : m_systems)
	{
		el.second->init( *r_world );
	}
	m_isInit = true;
}
