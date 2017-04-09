#include "ItemComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::ItemComponent::ItemComponent( const Item * item )
	:item( item )
{
}

void nb::ItemComponent::init()
{
	r_spriteComponent = component<SpriteComponent>();
	r_physicsComponent = component<PhysicsComponent>();

	r_spriteComponent->setTexture( *item->getTextureReference() );

	r_physicsComponent->s_beginCollision.connect( [&]( PhysicsComponent* other ) {
		cout << "coll" << endl;
	} );
}

void nb::ItemComponent::destroy()
{
}
