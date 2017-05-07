#include "TilePaintGameState.h"
using namespace std;
using namespace sf;
using namespace nb;
using namespace tgui;

nb::TilePaintGameState::TilePaintGameState( World & world,
											Entity* camera )
	: world( world ),
	camera( camera )
{}

void nb::TilePaintGameState::init( const CoreEngineManager& coreEngines,
								   GameStateManager& gameStates )
{
	r_resourceEngine = coreEngines.getEngine<ResourceEngine>();
	r_inputEngine = coreEngines.getEngine<InputEngine>();
	r_graphicsEngine = coreEngines.getEngine<GraphicsEngine>();
	r_gui = coreEngines.getEngine<GraphicsEngine>()->getGui();

	childWindow = ChildWindow::create();
	childWindow->setSize( {200,200} );
	childWindow->setTitle( "Tile Paint" );
	childWindow->keepInParent( true );
	childWindow->connect( "Closed", [&] (){
		this->close();
	} );

	tileListBox = ListBox::create();
	tileListBox->setSize( "{parent.width, parent.height}" );
	tileListBox->connect( "ItemSelected", [&] ( const sf::String& itemName,
												const sf::String& id ){
		if( tileListBox->getSelectedItem().getSize() )
			tileToPaint = std::stoi( id.toAnsiString() );
	} );

	//add tiles to list
	for( auto& tile : r_resourceEngine->tiles.getAllTiles() )
	{
		tileListBox->addItem( tile.getName(), to_string( tile.getId() ) );
	}

	childWindow->add( tileListBox );
	r_gui->add( childWindow );

	r_inputEngine->s_whileMouseButtonPressedInWindow[ Mouse::Button::Left ].connect_track( connections, [&] ( const sf::Vector2i& positionInWindow ){
		if( r_graphicsEngine->isGuiFocused() )
			return;

		const auto& cameraView = camera->getComponent<CameraComponent>()->getView();
		const auto& cameraPosition = camera->getComponent<TransformationComponent>()->getPosition();
		auto mappedPosition = r_graphicsEngine->getWindow().mapPixelToCoords( positionInWindow,
																			  cameraView );
		auto pixelPositionInWorld = Vector3i( mappedPosition.x,
											  mappedPosition.y,
											  cameraPosition.z );
		auto chunkPositionInWorld = ChunkSystem::calculateChunkPositionForPixelPosition( pixelPositionInWorld );
		auto tilePositionInWorld = Tile::calculateTilePositionForPixelPosition( pixelPositionInWorld );
		auto terrainToModifyVec = world.getSystem<ChunkSystem>()->getEntitiesInChunk_if( chunkPositionInWorld, [&] ( const Entity* entity ){
			return( entity->getComponent_try<TileMapComponent>() != nullptr );
		} );
		if( terrainToModifyVec.size() == 1 )
		{
			auto terrainToModify = terrainToModifyVec.at( 0 )->getComponent<TileMapComponent>();
			auto relativeTilePosition = terrainToModify->calculateRelativeTilePosition( tilePositionInWorld );
			auto tileToSet = r_resourceEngine->tiles.getTile( tileToPaint );
			if( tileToSet->getId() != terrainToModify->getTile( relativeTilePosition )->getId() )
				terrainToModify->setTiles( {{ relativeTilePosition, tileToSet }} );
		}
	} );
}

void nb::TilePaintGameState::update( GameStateManager& gameStates )
{}

void nb::TilePaintGameState::destroy( GameStateManager& gameStates )
{
	r_gui->remove( childWindow );
}
