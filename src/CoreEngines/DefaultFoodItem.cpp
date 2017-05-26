#include "DefaultFoodItem.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::DefaultFoodItem::DefaultFoodItem( const std::string name,
									  const TextureReference * texture,
									  const float hungerPerUse,
									  const float thirstPerUse,
									  const float energyPerUse,
									  const unsigned int uses )
	: Item( move( name ),
			texture,
			"Eat / Drink" ),
	hungerPerUse( hungerPerUse ),
	thirstPerUse( thirstPerUse ),
	energyPerUse( energyPerUse ),
	usesLeft( uses )
{}

void nb::DefaultFoodItem::use( World & world,
							   Entity * entity )
{
	if( usesLeft )
	{
		auto needsComponent = entity->getComponent_try<NeedsComponent>();
		if( needsComponent )
		{
			needsComponent->changeHunger( hungerPerUse );
			needsComponent->changeThirst( thirstPerUse );
			needsComponent->changeEnergy( energyPerUse );

			usesLeft--;
			if( !usesLeft )
			{
				auto inventoryComponent = entity->getComponent_try<InventoryComponent>();

				if( inventoryComponent )
				{
					if( inventoryComponent->inventory.containsItem( this ) )
					{
						// this pointer is invalid after call to removeItem
						// do not try to access members after the folowing line
						inventoryComponent->inventory.removeItem( this );
					}
				}
			}
		}
	}
}
