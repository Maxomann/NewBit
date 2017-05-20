#include "ItemPickupComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ItemPickupComponent::init()
{
	auto thisEntity = entity();

	inventoryComponent = thisEntity->getComponent<InventoryComponent>();
	physicsComponent = thisEntity->getComponent<PhysicsComponent>();

	auto onCollision = [&] ( const PhysicsComponent* other ){
		auto otherEntity = other->getEntity();

		auto itemComponent = otherEntity->getComponent_try<ItemComponent>();
		if( itemComponent )
		{
			inventoryComponent->inventory.addItem( itemComponent->moveItem() );
		}
	};

	physicsComponent->s_beginCollision.connect( onCollision );
}
