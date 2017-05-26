#include "DefaultFoodItemFactory.h"
#include "ResourceEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::DefaultFoodItemFactory::DefaultFoodItemFactory( ID id,
													NAME name,
													LABELS labels,
													const TextureReference* texture,
													const float hungerPerUse,
													const float thirstPerUse,
													const float energyPerUse,
													const unsigned int uses )
	: ItemFactory( id, move( name ), move( labels ) ),
	texture( texture ),
	hungerPerUse( hungerPerUse ),
	thirstPerUse( thirstPerUse ),
	energyPerUse( energyPerUse ),
	uses( uses )
{}

std::unique_ptr<Item> nb::DefaultFoodItemFactory::create() const
{
	return make_unique<DefaultFoodItem>( getName(),
										 texture,
										 hungerPerUse,
										 thirstPerUse,
										 energyPerUse,
										 uses );
}
