#include "InventoryViewGameState.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

void nb::InventoryViewGameState::updateView( const Inventory& inventoryForUpdate )
{
	inventoryListContainer->removeAllWidgets();

	int counter = 0;

	for( const auto& item : inventoryForUpdate.getContent() )
	{
		Panel::Ptr objectContainer = Panel::create();
		objectContainer->setSize( 300, 60 );
		objectContainer->setPosition( 0, 60 * counter );
		objectContainer->getRenderer()->setBackgroundColor( sf::Color::White );

		/*Picture::Ptr picture = Picture::create();
		picture->setSize( 60, 60 );*/

		Label::Ptr label = Label::create();
		label->setSize( 200, 60 );
		label->setPosition( 60, 0 );
		label->setText( item->getName() );

		Button::Ptr useButton = Button::create();
		useButton->setSize( 40, 40 );
		useButton->setPosition( 260, 0 );
		useButton->setText( "Use" );

		//objectContainer->add( picture );
		objectContainer->add( label );
		objectContainer->add( useButton );

		inventoryListContainer->add( objectContainer );

		counter++;
	}
}

nb::InventoryViewGameState::InventoryViewGameState( World& world,
													Entity* entityToApplyActions,
													Inventory& inventory )
	: world( world ),
	entityToApplyActions( entityToApplyActions ),
	inventory( inventory )
{}

void nb::InventoryViewGameState::init( const CoreEngineManager& coreEngines,
									   GameStateManager& gameStates )
{
	graphics = coreEngines.getEngine<GraphicsEngine>();
	resources = coreEngines.getEngine<ResourceEngine>();

	inventoryListContainer = Panel::create();
	inventoryListContainer->setSize( {300, 500} );
	inventoryListContainer->setPosition( 700, "( parent.height - height ) / 2" );
	graphics->getGui()->add( inventoryListContainer );

	inventory.s_contentChange.connect_track( connections, this, &InventoryViewGameState::updateView );

	updateView( inventory );
}

void nb::InventoryViewGameState::update( GameStateManager& gameStates )
{}

void nb::InventoryViewGameState::destroy( GameStateManager& gameStates )
{
	graphics->getGui()->remove( inventoryListContainer );
}
