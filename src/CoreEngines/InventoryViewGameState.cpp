#include "InventoryViewGameState.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

const tgui::Color InventoryViewGameState::inactiveColor = tgui::Color {102, 102, 102};
const tgui::Color InventoryViewGameState::activeColor = tgui::Color {245, 245, 245};

void nb::InventoryViewGameState::updateView( const Inventory& inventoryForUpdate )
{
	itemList->removeAllItems();
	selectedItemId = -1;

	int counter = 0;

	for( const auto& item : inventoryForUpdate.getContent() )
	{
		itemList->addItem( item->getName(), to_string( counter ) );
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

	inventoryListContainer = ChildWindow::create();
	inventoryListContainer->setSize( {300, 360} );
	inventoryListContainer->setTitle( "Inventory" );
	inventoryListContainer->keepInParent( true );
	inventoryListContainer->setTitleButtons( ChildWindow::TitleButton::None );

	itemList = ListBox::create();
	itemList->setSize( {300, 280} );
	itemList->setPosition( {0,40} );

	useButton = Button::create();
	useButton->setSize( {300, 40} );
	useButton->setPosition( {0, 320} );
	useButton->setText( "Use" );
	useButton->getRenderer()->setBackgroundColor( inactiveColor );
	useButton->getRenderer()->setBackgroundColorHover( inactiveColor );

	inventoryListContainer->add( itemList );
	inventoryListContainer->add( useButton );

	itemList->connect( "ItemSelected", [&] ( const string& name, const string& id ){
		// select
		if( itemList->getSelectedItem().getSize() > 0 )
		{
			selectedItemId = atoi( id.c_str() );

			if( inventory.getContent().at( selectedItemId )->canBeUsed() )
			{
				useButton->getRenderer()->setBackgroundColor( activeColor );
				useButton->getRenderer()->setBackgroundColorHover( activeColor );
			}
			else
			{
				useButton->getRenderer()->setBackgroundColor( inactiveColor );
				useButton->getRenderer()->setBackgroundColorHover( inactiveColor );
			}
		}
		else
		{
			selectedItemId = -1;
			useButton->getRenderer()->setBackgroundColor( inactiveColor );
			useButton->getRenderer()->setBackgroundColorHover( inactiveColor );
		}
	} );
	itemList->connect( "DoubleClicked", [&] ( const string& name, const string& id ){
		// drop

		if( itemList->getSelectedItem().getSize() > 0 )
		{
			int clickedItemId = atoi( id.c_str() );

			auto item = inventory.moveItem( clickedItemId );

			auto spawnPosition = entityToApplyActions->getComponent<TransformationComponent>()->getPosition();
			spawnPosition.xy += Vector2f( 0, 60 );

			world.addEntity( ItemManager::createItemEntity( move( item ), spawnPosition ) );
		}
	} );
	useButton->connect( "Pressed", [&] (){
		// try to use

		if( selectedItemId >= 0 )
		{
			const auto& selectedItem = inventory.getContent().at( selectedItemId );

			if( selectedItem->canBeUsed() )
				selectedItem->use( world, entityToApplyActions );
		}
	} );

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
