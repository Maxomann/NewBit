#include "Entity.h"
using namespace std;
using namespace nb;

Entity::Entity( Entity&& entity )
{
	m_components = move( entity.m_components );
	m_isInit = move( entity.m_isInit );
	outsideConnections = move( entity.outsideConnections );

	// Update Entity references for components in this entity
	// Note: This is important, since entities can be moved after being initalized (ex. when an entity is initialized in a thread and added to the world after)
	for (const auto& el : m_components)
		el.second->linkToEntity( this );
}

void nb::Entity::init()
{
	if (m_isInit)
	{
		throw exception::EntityAlreadyInitializedException();
	}
	else
	{
		// init components
		for (auto& el : m_components)
		{
			el.second->init();
		}
		m_isInit = true;
	}
}

bool nb::Entity::isInit() const
{
	return m_isInit;
}

void nb::Entity::destroy()
{
	for (auto& el : m_components)
		el.second->destroy();
	m_isInit = false;
}
