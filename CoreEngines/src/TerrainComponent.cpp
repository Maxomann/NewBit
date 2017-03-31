#include "TerrainComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

const int TerrainComponent::TILE_SIZE_IN_PIXEL = 32;
const int TerrainComponent::TERRAIN_SIZE_IN_PIXEL = 640;
const int TerrainComponent::TILES_PER_TERRAIN = 20; // = 640/32

nb::TerrainComponent::TerrainComponent( const Tile* defaultTile )
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

nb::TerrainComponent::TerrainComponent( const Tile* defaultTile, std::map<sf::Vector2i, const Tile*> tileTexturesByPosition )
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

nb::TerrainComponent::TerrainComponent( std::vector<std::vector<const Tile*>> tiles )
	: tiles( move( tiles ) )
{
	generate();
}

nb::TerrainComponent::~TerrainComponent()
{
	if (generationFuture.valid() &&
		 generationFuture.wait_for( chrono::microseconds( 0 ) ) != future_status::ready)
		generationFuture.wait();// prevent thread from accessing vertexArrays after destrucion
}

void TerrainComponent::init()
{
	auto entity = getEntity();

	//connections
	auto transform = entity->getComponent<TransformationComponent>();
	transform->s_positionXYChanged.connect( [&]( const TransformationComponent*const transform,
												 sf::Vector2i oldPositionXY ) {
		//do nothing
	} );
	transform->s_sizeChanged.connect( [&]( const TransformationComponent*const transform,
										   sf::Vector2u oldSize ) {
		throw std::logic_error( "Cannot size Terrain" );
	} );
	transform->s_rotationChanged.connect( [&]( const TransformationComponent*const transform,
											   float oldRotation ) {
		throw std::logic_error( "Cannot rotate Terrain" );
	} );

	auto render = entity->getComponent<RenderComponent>();
	render->addDrawable( this );
};

void TerrainComponent::destroy()
{
	return;
};

void nb::TerrainComponent::setTiles( std::map<sf::Vector2i, const Tile*> tilesByPosition )
{
	for (auto& el : tilesByPosition)
		tiles.at( el.first.x ).at( el.first.y ) = el.second;
	generate();
}

void nb::TerrainComponent::generate()
{
	if (generationFuture.valid() &&
		 generationFuture.wait_for( chrono::microseconds( 0 ) ) != future_status::ready)
		generationFuture.wait();// this is expensive, since it has to wait for generate_internal() to finish!

	generationFuture = std::async( std::launch::async, &TerrainComponent::generate_internal, this );
}

void nb::TerrainComponent::generate_internal()
{
	vertexArrays.clear();

	for (int x = 0; x < TILES_PER_TERRAIN; ++x)
	{
		for (int y = 0; y < TILES_PER_TERRAIN; ++y)
		{
			const auto& texRef = *tiles.at( x ).at( y )->getTextureReference();
			const auto& defaultTexRect = texRef.getDefaultTextureRect();

			vertexArrays[&texRef.getTexture()].push_back( sf::Vertex(
				sf::Vector2f( x*TILE_SIZE_IN_PIXEL,
							  y*TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left,
							  defaultTexRect.top ) ) );
			vertexArrays[&texRef.getTexture()].push_back( sf::Vertex(
				sf::Vector2f( (x*TILE_SIZE_IN_PIXEL) + TILE_SIZE_IN_PIXEL,
							  y*TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left + defaultTexRect.width,
							  defaultTexRect.top ) ) );
			vertexArrays[&texRef.getTexture()].push_back( sf::Vertex(
				sf::Vector2f( (x*TILE_SIZE_IN_PIXEL) + TILE_SIZE_IN_PIXEL,
				(y*TILE_SIZE_IN_PIXEL) + TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left + defaultTexRect.width,
							  defaultTexRect.top + defaultTexRect.height ) ) );
			vertexArrays[&texRef.getTexture()].push_back( sf::Vertex(
				sf::Vector2f( x*TILE_SIZE_IN_PIXEL,
				(y*TILE_SIZE_IN_PIXEL) + TILE_SIZE_IN_PIXEL ),
				sf::Vector2f( defaultTexRect.left,
							  defaultTexRect.top + defaultTexRect.height ) ) );
		}
	}
}

void nb::TerrainComponent::draw( sf::RenderTarget & target,
								 sf::RenderStates states )const
{
	if (!generationFuture.valid() ||
		 generationFuture.wait_for( chrono::microseconds( 0 ) ) == future_status::ready)
	{
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
}
