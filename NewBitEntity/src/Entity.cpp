#include "Entity.h"
using namespace std;
using namespace nb;

Entity::Entity( Entity&& entity )
{
	m_components = move( entity.m_components );
	m_isInit = move( entity.m_isInit );

	// Update Entity references for components in this entity
	// Note: This may not be needed, since entities are initialized *after* being placed in the entity list
	for (const auto& el : m_components)
		el.second->linkToEntity( this );
}

void nb::Entity::init()
{
	if (m_isInit)
	{
		throw exception::EntityAlreadyInitializedException();
	}
	for (auto& el : m_components)
	{
		el.second->init();
	}
	m_isInit = true;
}

void nb::Entity::destroy()
{
	for (auto& el : m_components)
		el.second->destroy();
}
