#include "EntityTrackerScreenGameState.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

void nb::EntityTrackerScreenGameState::init( const CoreEngineManager& coreEngines,
											 GameStateManager& gameStates )
{
	r_gui = coreEngines.getEngine<GraphicsEngine>()->getGui();

	// GUI
	m_playerStatsWindow = ChildWindow::create();
	m_playerStatsWindow->setTitle( "Entity Stats" );
	m_playerStatsWindow->setSize( Layout2d( 400, 300 ) );
	m_playerStatsWindow->setPosition( Layout2d( 0, 0 ) );
	m_playerStatsWindow->keepInParent( true );
	m_playerStatsWindow->setTitleButtons( ChildWindow::TitleButton::None );

	m_playerPositionLabel = Label::create();
	m_playerPositionLabel->setSize( Layout2d( 200, 60 ) );
	m_playerPositionLabel->setPosition( Layout2d( 0, 0 ) );
	m_playerPositionLabel->setText( "Position:" );
	m_playerStatsWindow->add( m_playerPositionLabel );

	m_playerPositionValueLabel = Label::create();
	m_playerPositionValueLabel->setSize( Layout2d( 200, 60 ) );
	m_playerPositionValueLabel->setPosition( Layout2d( 200, 0 ) );
	m_playerPositionValueLabel->setText( "Not Available" );
	m_playerStatsWindow->add( m_playerPositionValueLabel );

	m_playerSpritePathLabel = Label::create();
	m_playerSpritePathLabel->setSize( Layout2d( 200, 40 ) );
	m_playerSpritePathLabel->setPosition( Layout2d( 0, 60 ) );
	m_playerSpritePathLabel->setText( "GlTextureHandle:" );
	m_playerStatsWindow->add( m_playerSpritePathLabel );

	m_playerSpritePathValueLabel = Label::create();
	m_playerSpritePathValueLabel->setSize( Layout2d( 200, 40 ) );
	m_playerSpritePathValueLabel->setPosition( Layout2d( 200, 60 ) );
	m_playerSpritePathValueLabel->setText( "Not Available" );
	m_playerStatsWindow->add( m_playerSpritePathValueLabel );

	m_playerHealthLabel = Label::create();
	m_playerHealthLabel->setSize( Layout2d( 200, 40 ) );
	m_playerHealthLabel->setPosition( Layout2d( 0, 100 ) );
	m_playerHealthLabel->setText( "Health:" );
	m_playerStatsWindow->add( m_playerHealthLabel );

	m_playerHealthValueLabel = Label::create();
	m_playerHealthValueLabel->setSize( Layout2d( 200, 40 ) );
	m_playerHealthValueLabel->setPosition( Layout2d( 200, 100 ) );
	m_playerHealthValueLabel->setText( "Not Available" );
	m_playerStatsWindow->add( m_playerHealthValueLabel );

	m_playerHungerLabel = Label::create();
	m_playerHungerLabel->setSize( Layout2d( 200, 40 ) );
	m_playerHungerLabel->setPosition( Layout2d( 0, 140 ) );
	m_playerHungerLabel->setText( "Hunger:" );
	m_playerStatsWindow->add( m_playerHungerLabel );

	m_playerHungerValueLabel = Label::create();
	m_playerHungerValueLabel->setSize( Layout2d( 200, 40 ) );
	m_playerHungerValueLabel->setPosition( Layout2d( 200, 140 ) );
	m_playerHungerValueLabel->setText( "Not Available" );
	m_playerStatsWindow->add( m_playerHungerValueLabel );

	inventoryList = ListBox::create();
	inventoryList->setSize( Layout2d( 400, 80 ) );
	inventoryList->setPosition( Layout2d( 0, 180 ) );
	m_playerStatsWindow->add( inventoryList );

	r_gui->add( m_playerStatsWindow );
}

void nb::EntityTrackerScreenGameState::update( GameStateManager& gameStates )
{}

void nb::EntityTrackerScreenGameState::destroy( GameStateManager& gameStates )
{
	r_gui->remove( m_playerStatsWindow );
}

void nb::EntityTrackerScreenGameState::track( const Entity* entity )
{
	m_connections.clear();

	auto transform = entity->getComponent_try<TransformationComponent>();
	if( transform )
	{
		auto position = transform->getPosition();
		m_playerPositionValueLabel->setText( "X: " + to_string( position.xy.x ) + "\n" +
											 "Y: " + to_string( position.xy.y ) + "\n" +
											 "Z: " + to_string( position.layer ) );
		transform->s_positionChanged.connect_track( m_connections, [&] ( const TransformationComponent* const comp,
																		 const Position& oldPosition ){
			auto position = comp->getPosition();
			m_playerPositionValueLabel->setText( "X: " + to_string( position.xy.x ) + "\n" +
												 "Y: " + to_string( position.xy.y ) + "\n" +
												 "Z: " + to_string( position.layer ) );
		} );
	}

	auto sprite = entity->getComponent_try<SpriteComponent>();
	if( sprite )
	{
		m_playerSpritePathValueLabel->setText( to_string( sprite->getSprite().getTexture()->getNativeHandle() ) );
	}

	auto health = entity->getComponent_try<HealthComponent>();
	if( health )
	{
		auto val = health->getHealth();
		m_playerHealthValueLabel->setText( to_string( val ) );
		health->s_onChange.connect_track( m_connections, [&] ( const HealthComponent* const comp,
															   int change ){
			m_playerHealthValueLabel->setText( to_string( comp->getHealth() ) + " / " + to_string( comp->getMaxHealth() ) );
		} );
	}

	auto needs = entity->getComponent_try<NeedsComponent>();
	if( needs )
	{
		auto val = needs->getHunger();
		m_playerHungerValueLabel->setText( to_string( val ) );
		needs->s_hungerChanged.connect_track( m_connections, [&] ( const NeedsComponent* const comp,
																   float oldHunger ){
			m_playerHungerValueLabel->setText( to_string( comp->getHunger() ) );
		} );
	}

	auto inventory = entity->getComponent_try<InventoryComponent>();
	if( inventory )
	{
		auto refreshInventoryList = [&] ( const Inventory& inventory ){
			inventoryList->removeAllItems();
			const auto& data = inventory.getContent();
			for( const auto& item : data )
			{
				auto itemName = item->getName();

				auto str = itemName + " : " + to_string( item->canBeUsed() );
				inventoryList->addItem( str );
			}
		};

		refreshInventoryList( inventory->inventory );
		inventory->inventory.s_contentChange.connect_track( m_connections, refreshInventoryList );
	}
}
