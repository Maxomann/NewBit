#include "TerrainComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

const int TerrainComponent::TILE_SIZE_IN_PIXEL = 32;
const int TerrainComponent::TERRAIN_SIZE_IN_PIXEL = 640;
const int TerrainComponent::TILES_PER_TERRAIN = 20; // = 640/32

nb::TerrainComponent::TerrainComponent( TextureReference defaultTile )
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

nb::TerrainComponent::TerrainComponent( std::vector<std::vector<TextureReference>> tiles )
	: tiles( move( tiles ) )
{
	generate();
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

void nb::TerrainComponent::setTiles( std::map<sf::Vector2i, TextureReference> tileTexturesByPosition )
{
	for (auto& el : tileTexturesByPosition)
		tiles.at( el.first.x ).at( el.first.y ) = el.second;
	generate();
}

void nb::TerrainComponent::generate()
{
	vertexArrays.clear();

	for (int x = 0; x < TILES_PER_TERRAIN; ++x)
	{
		for (int y = 0; y < TILES_PER_TERRAIN; ++y)
		{
			const auto& texRef = tiles.at( x ).at( y );
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
