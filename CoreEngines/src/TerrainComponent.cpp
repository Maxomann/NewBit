#include "TerrainComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

const int TerrainComponent::TILE_SIZE_IN_PIXEL = 32;

nb::TerrainComponent::TerrainComponent( const TextureReference & debugTexture )
{
	setDebugTexture( debugTexture );
}

void nb::TerrainComponent::setSize( sf::Vector2u size )
{
	auto& texrect = m_debugSprite.getTextureRect();
	auto& scale = m_debugSprite.getScale();
	const auto& newSize = size;
	m_debugSprite.setScale( newSize.x / (texrect.width*scale.x), newSize.y / (texrect.height*scale.y) );
}

void TerrainComponent::init()
{
	auto entity = getEntity();

	auto transform = entity->getComponent<TransformationComponent>();
	//default values
	m_debugSprite.setPosition( Vector2f( transform->getPositionXY() ) );
	setSize( transform->getSize() );

	//connections
	transform->s_positionXYChanged.connect( [&]( const TransformationComponent*const transform,
												 sf::Vector2i oldPositionXY ) {
		m_debugSprite.setPosition( Vector2f( transform->getPositionXY() ) );
	} );
	transform->s_sizeChanged.connect( [&]( const TransformationComponent*const transform,
										   sf::Vector2u oldSize ) {
		setSize( transform->getSize() );
	} );
	transform->s_rotationChanged.connect( [&]( const TransformationComponent*const transform,
											   float oldRotation ) {
		throw std::logic_error( "Cannot rotate Terrain" );
	} );

	auto render = entity->getComponent<RenderComponent>();
	render->addDrawable( &m_debugSprite );
};

void TerrainComponent::destroy()
{
	return;
};

void nb::TerrainComponent::setDebugTexture( const TextureReference& texture )
{
	texture.applyTextureAndDefaultTextureRectToSprite( m_debugSprite );
	auto& defaultRect = texture.getDefaultTextureRect();
}
