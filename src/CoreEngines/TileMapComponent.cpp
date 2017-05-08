#include "TileMapComponent.h"
#include "ChunkSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

const int TileMapComponent::TILE_SIZE_IN_PIXEL = Tile::TILE_SIZE_IN_PIXEL;
const int TileMapComponent::TERRAIN_SIZE_IN_PIXEL = 640;
const int TileMapComponent::TILES_PER_TERRAIN = 20; // = 640(TERRAIN_SIZE_IN_PIXEL) / 32(TILE_SIZE_IN_PIXEL)

void nb::TileMapComponent::calculateGlobalBounds()
{
	const auto transformPositionXY = component<TransformationComponent>()->getPositionXY();
	globalBounds = FloatRect(
		transformPositionXY.x,
		transformPositionXY.y,
		TERRAIN_SIZE_IN_PIXEL,
		TERRAIN_SIZE_IN_PIXEL
	);
}

nb::TileMapComponent::TileMapComponent( const Tile* defaultTile )
{
	for (int x = 0; x < TILES_PER_TERRAIN; ++x)
	{
		tiles.emplace_back();
		for (int y = 0; y < TILES_PER_TERRAIN; ++y)
		{
			tiles.at( x ).emplace_back( defaultTile );
		}
	}
	generate();
}

nb::TileMapComponent::TileMapComponent( const Tile* defaultTile, std::map<sf::Vector2i, const Tile*> tileTexturesByPosition )
{
	for (int x = 0; x < TILES_PER_TERRAIN; ++x)
	{
		tiles.emplace_back();
		for (int y = 0; y < TILES_PER_TERRAIN; ++y)
		{
			tiles.at( x ).emplace_back( defaultTile );
		}
	}
	for (auto& el : tileTexturesByPosition)
		tiles.at( el.first.x ).at( el.first.y ) = el.second;
	generate();
}

nb::TileMapComponent::TileMapComponent( std::vector<std::vector<const Tile*>> tiles )
	: tiles( move( tiles ) )
{
	generate();
}

nb::TileMapComponent::~TileMapComponent()
{
	if (generationFuture.valid() &&
		 generationFuture.wait_for( chrono::microseconds( 0 ) ) != future_status::ready)
		generationFuture.wait();// prevent thread from accessing vertexArrays after destrucion
}

void TileMapComponent::init()
{
	auto entity = getEntity();

	//connections
	auto transform = entity->getComponent<TransformationComponent>();
	transform->s_positionXYChanged.connect( [&]( const TransformationComponent*const transform,
												 sf::Vector2i oldPositionXY ) {
		calculateGlobalBounds();
	} );
	transform->s_sizeChanged.connect( [&]( const TransformationComponent*const transform,
										   sf::Vector2f oldSize ) {
		throw std::logic_error( "Cannot size Terrain" );
	} );
	transform->s_rotationChanged.connect( [&]( const TransformationComponent*const transform,
											   float oldRotation ) {
		throw std::logic_error( "Cannot rotate Terrain" );
	} );

	calculateGlobalBounds();

	auto render = entity->getComponent<RenderComponent>();
	render->addDrawable( this, &globalBounds );
};

void nb::TileMapComponent::setTiles( std::map<sf::Vector2i, const Tile*> tilesByPosition )
{
	for (auto& el : tilesByPosition)
		tiles.at( el.first.x ).at( el.first.y ) = el.second;
	generate();
}

const Tile * nb::TileMapComponent::getTile( sf::Vector2i relativePosition ) const
{
	return tiles.at( relativePosition.x ).at( relativePosition.y );
}

void nb::TileMapComponent::generate()
{
	if (generationFuture.valid() &&
		 generationFuture.wait_for( chrono::microseconds( 0 ) ) != future_status::ready)
		generationFuture.wait();// this is expensive, since it has to wait for generate_internal() to finish!

	generationFuture = std::async( std::launch::async, &TileMapComponent::generate_internal, this );
}

void nb::TileMapComponent::generate_internal()
{
	std::map<const sf::Texture*, std::vector<sf::Vertex>>vertexArraysBuffer;

	for (int x = 0; x < TILES_PER_TERRAIN; ++x)
	{
		for (int y = 0; y < TILES_PER_TERRAIN; ++y)
		{
			const auto& texRef = *tiles.at( x ).at( y )->getTextureReference();
			const auto& defaultTexRect = texRef.getDefaultTextureRect();

			vertexArraysBuffer[&texRef.getTexture()].push_back( sf::Vertex(
				sf::Vector2f( x*TILE_SIZE_IN_PIXEL,
							  y*TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left,
							  defaultTexRect.top ) ) );
			vertexArraysBuffer[&texRef.getTexture()].push_back( sf::Vertex(
				sf::Vector2f( (x*TILE_SIZE_IN_PIXEL) + TILE_SIZE_IN_PIXEL,
							  y*TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left + defaultTexRect.width,
							  defaultTexRect.top ) ) );
			vertexArraysBuffer[&texRef.getTexture()].push_back( sf::Vertex(
				sf::Vector2f( (x*TILE_SIZE_IN_PIXEL) + TILE_SIZE_IN_PIXEL,
				(y*TILE_SIZE_IN_PIXEL) + TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left + defaultTexRect.width,
							  defaultTexRect.top + defaultTexRect.height ) ) );
			vertexArraysBuffer[&texRef.getTexture()].push_back( sf::Vertex(
				sf::Vector2f( x*TILE_SIZE_IN_PIXEL,
				(y*TILE_SIZE_IN_PIXEL) + TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left,
							  defaultTexRect.top + defaultTexRect.height ) ) );
		}
	}

	lock_guard<mutex> lock( vertexArraysMutex );
	vertexArrays = move( vertexArraysBuffer );
}

void nb::TileMapComponent::draw( sf::RenderTarget & target,
								 sf::RenderStates states )const
{
	lock_guard<mutex> lock( vertexArraysMutex );

	sf::Transform trans;
	trans.translate( sf::Vector2f( component<TransformationComponent>()->getPositionXY() ) );
	states.transform *= trans;

	for (auto& el : vertexArrays)
	{
		states.texture = el.first;

		auto& vertices = el.second;
		target.draw( &vertices.at( 0 ), vertices.size(), sf::Quads, states );
	}
}

sf::Vector2i nb::TileMapComponent::calculateRelativeTilePosition( sf::Vector3i absoluteTilePosition )
{
	Vector2i retVal;

	auto thisPixelPosition = component<TransformationComponent>()->getPosition();
	if (thisPixelPosition.z != absoluteTilePosition.z)
		throw std::logic_error( "nb::TileMapComponent::calculateRelativeTilePosition | thisPixelPosition.z != absoluteTilePosition.z" );

	auto thisChunkPosition = ChunkSystem::calculateChunkPositionForPixelPosition( thisPixelPosition );

	retVal.x = abs( absoluteTilePosition.x ) % TILES_PER_TERRAIN;

	retVal.y = abs( absoluteTilePosition.y ) % TILES_PER_TERRAIN;

	if (thisChunkPosition.x < 0 && retVal.x != 0)
		retVal.x = TILES_PER_TERRAIN - retVal.x;
	if (thisChunkPosition.y < 0 && retVal.y != 0)
		retVal.y = TILES_PER_TERRAIN - retVal.y;

	return retVal;
}
