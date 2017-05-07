#include "EntityFactory.h"
using namespace std;
using namespace nb;

nb::EntityFactory::EntityFactory( ID id, NAME name, LABELS labels )
	:id( id ), name( name ), labels( labels )
{
}

EntityFactory::ID nb::EntityFactory::getId() const
{
	return id;
}

const EntityFactory::NAME & nb::EntityFactory::getName() const
{
	return name;
}

const EntityFactory::LABELS & nb::EntityFactory::getLabels() const
{
	return labels;
}
