#include "Entity.h"

void nb::entity::Entity::init()
{
	if ( m_isInit )
	{
		throw exception::EntityAlreadyInitializedException();
	}
	for ( auto& el : m_components )
	{
		el.second->init( *this );
	}
	m_isInit = true;
}

void nb::entity::Entity::destroy()
{
	for ( auto& el : m_components )
		el.second->destroy( *this );
}