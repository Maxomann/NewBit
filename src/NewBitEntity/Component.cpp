#include "Component.h"
using namespace nb;

void Component::linkToEntity( Entity* entity )
{
	r_entity = entity;
};

Entity* Component::getEntity()const
{
	return r_entity;
};

Entity * nb::Component::entity() const
{
	return r_entity;
}
