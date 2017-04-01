#include "TilePaintGameState.h"
using namespace std;
using namespace sf;
using namespace nb;
using namespace tgui;

void nb::TilePaintGameState::init()
{
	r_gui = getCore()->engines.getEngine<GuiEngine>()->getGui();

	childWindow = ChildWindow::create();
	childWindow->setSize( { 200,200 } );
	childWindow->setTitle( "Tile Paint" );
	childWindow->keepInParent( true );
	childWindow->connect( "Closed", [&]() {
		isWindowOpen = false;
	} );

	tileListBox = ListBox::create();
	tileListBox->setSize( "{parent.width, parent.height}" );
	tileListBox->connect( "ItemSelected", [&]( const sf::String& itemName,
											   const sf::String& id ) {
		tileToPaint = std::stoi( id.toAnsiString() );
	} );

	//add tiles to list
	for (auto& tile : engine<ResourceEngine>()->tiles.getAllTiles())
	{
		tileListBox->addItem( tile.getName(), to_string( tile.getId() ) );
	}

	childWindow->add( tileListBox );
	r_gui->add( childWindow );

	engine<InputEngine>()->s_whileMouseButtonPressedInWindow[Mouse::Button::Left].connect( [&]( const sf::Vector2i& positionInWindow ) {
		if (engine<GuiEngine>()->isGuiFocused())
			return;

		const auto& camera = world().getSystem<RenderSystem>()->getCamerasForDrawing().at( 0 );
		const auto& cameraView = camera->getComponent<CameraComponent>()->getView();
		const auto& cameraPosition = camera->getComponent<TransformationComponent>()->getPosition();
		auto mappedPosition = engine<GraphicsEngine>()->getWindow().mapPixelToCoords( positionInWindow,
																					  cameraView );
		auto pixelPositionInWorld = Vector3i( mappedPosition.x,
											  mappedPosition.y,
											  cameraPosition.z );
		auto chunkPositionInWorld = ChunkSystem::calculateChunkPositionForPixelPosition( pixelPositionInWorld );
		auto tilePositionInWorld = Tile::calculateTilePositionForPixelPosition( pixelPositionInWorld );
		auto terrainToModifyVec = world().getSystem<ChunkSystem>()->getEntitiesInChunk_if( chunkPositionInWorld, [&]( const Entity* entity ) {
			return(entity->getComponent_try<TerrainComponent>() != nullptr);
		} );
		if (terrainToModifyVec.size() == 1)
		{
			auto terrainToModify = terrainToModifyVec.at( 0 )->getComponent<TerrainComponent>();
			auto relativeTilePosition = terrainToModify->calculateRelativeTilePosition( tilePositionInWorld );
			auto tileToSet = engine<ResourceEngine>()->tiles.getTile( tileToPaint );
			if (tileToSet->getId() != terrainToModify->getTile( relativeTilePosition )->getId())
				terrainToModify->setTiles( { { relativeTilePosition, tileToSet } } );
		}
	} );
}

void nb::TilePaintGameState::update()
{
}

void nb::TilePaintGameState::destroy()
{
	r_gui->remove( childWindow );
}

bool nb::TilePaintGameState::shouldDestroy()
{
	return !isWindowOpen;
}
