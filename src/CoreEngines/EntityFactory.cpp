#include "EntityFactory.h"
using namespace std;
using namespace nb;

nb::EntityFactory::EntityFactory( ID id, NAME name, LABELS labels )
	: Factory<Entity, const ResourceEngine&>( id, move( name ) ), labels( labels )
{}

const EntityFactory::LABELS & nb::EntityFactory::getLabels() const
{
	return labels;
}
