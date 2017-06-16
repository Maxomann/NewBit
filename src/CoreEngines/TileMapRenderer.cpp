#include "TileMapRenderer.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::TileMapRenderer::calculateGlobalBounds()
{
	const auto transformPositionXY = transform->getPositionXY();
	globalBounds = FloatRect(
		transformPositionXY.x,
		transformPositionXY.y,
		TileMapComponent::TERRAIN_SIZE_IN_PIXEL,
		TileMapComponent::TERRAIN_SIZE_IN_PIXEL
	);
}

void nb::TileMapRenderer::generate( const TileMapComponent::TileData& data )
{
	const auto dataCopy = data;

	if( generationFuture.valid() &&
		generationFuture.wait_for( chrono::microseconds( 0 ) ) != future_status::ready )
		generationFuture.wait();// this is expensive, since it has to wait for generate_internal() to finish!

	generationFuture = std::async( std::launch::async,
								   &TileMapRenderer::generate_internal,
								   this,
								   move( dataCopy ) );
}

void nb::TileMapRenderer::generate_internal( const TileMapComponent::TileData tiles )
{
	std::map<const sf::Texture*, std::vector<sf::Vertex>>vertexArraysBuffer;

	for( int x = 0; x < TileMapComponent::TILES_PER_TERRAIN; ++x )
	{
		for( int y = 0; y < TileMapComponent::TILES_PER_TERRAIN; ++y )
		{
			const auto& texRef = *tiles.at( x ).at( y )->getTextureReference();
			const auto& defaultTexRect = texRef.getDefaultTextureRect();

			vertexArraysBuffer[ &texRef.getTexture() ].push_back( sf::Vertex(
				sf::Vector2f( x*TileMapComponent::TILE_SIZE_IN_PIXEL,
							  y*TileMapComponent::TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left,
							  defaultTexRect.top ) ) );
			vertexArraysBuffer[ &texRef.getTexture() ].push_back( sf::Vertex(
				sf::Vector2f( ( x*TileMapComponent::TILE_SIZE_IN_PIXEL ) + TileMapComponent::TILE_SIZE_IN_PIXEL,
							  y*TileMapComponent::TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left + defaultTexRect.width,
							  defaultTexRect.top ) ) );
			vertexArraysBuffer[ &texRef.getTexture() ].push_back( sf::Vertex(
				sf::Vector2f( ( x*TileMapComponent::TILE_SIZE_IN_PIXEL ) + TileMapComponent::TILE_SIZE_IN_PIXEL,
				( y*TileMapComponent::TILE_SIZE_IN_PIXEL ) + TileMapComponent::TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left + defaultTexRect.width,
							  defaultTexRect.top + defaultTexRect.height ) ) );
			vertexArraysBuffer[ &texRef.getTexture() ].push_back( sf::Vertex(
				sf::Vector2f( x*TileMapComponent::TILE_SIZE_IN_PIXEL,
				( y*TileMapComponent::TILE_SIZE_IN_PIXEL ) + TileMapComponent::TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left,
							  defaultTexRect.top + defaultTexRect.height ) ) );
		}
	}

	lock_guard<mutex> lock( vertexArraysMutex );
	vertexArrays = move( vertexArraysBuffer );
}

nb::TileMapRenderer::~TileMapRenderer()
{
	if( generationFuture.valid() &&
		generationFuture.wait_for( chrono::microseconds( 0 ) ) != future_status::ready )
		generationFuture.wait();// prevent thread from accessing vertexArrays after destrucion
}

void nb::TileMapRenderer::init( const Entity * entity )
{
	transform = entity->getComponent<TransformationComponent>();
	tileMap = entity->getComponent<TileMapComponent>();

	//connections
	transform->s_positionXYChanged.connect( [&] ( const TransformationComponent*const transform,
												  sf::Vector2f oldPositionXY ){
		calculateGlobalBounds();
	} );
	transform->s_sizeChanged.connect( [&] ( const TransformationComponent*const transform,
											sf::Vector2f oldSize ){
		throw std::logic_error( "Cannot size Terrain" );
	} );
	transform->s_rotationChanged.connect( [&] ( const TransformationComponent*const transform,
												float oldRotation ){
		throw std::logic_error( "Cannot rotate Terrain" );
	} );

	tileMap->s_tilesChanged.connect( this, &TileMapRenderer::generate );

	calculateGlobalBounds();

	generate( tileMap->getTileData() );
}

const sf::FloatRect & nb::TileMapRenderer::getGlobalBounds() const
{
	return globalBounds;
}

void nb::TileMapRenderer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	lock_guard<mutex> lock( vertexArraysMutex );

	sf::Transform trans;
	trans.translate( sf::Vector2f( transform->getPositionXY() ) );
	states.transform *= trans;

	for( auto& el : vertexArrays )
	{
		states.texture = el.first;

		auto& vertices = el.second;
		target.draw( &vertices.at( 0 ), vertices.size(), sf::Quads, states );
	}
}
