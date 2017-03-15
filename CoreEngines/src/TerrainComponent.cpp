#include "TerrainComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

const int TerrainComponent::TILE_SIZE_IN_PIXEL = 32;

void nb::TerrainComponent::onPositionXYChanged( const TransformationComponent*const transform, sf::Vector2i oldPositionXY )
{
	m_debugSprite.setPosition( Vector2f( transform->getPositionXY() ) );
}

void nb::TerrainComponent::onSizeChanged( const TransformationComponent*const transform, sf::Vector2u oldSize )
{
	auto& texrect = m_debugSprite.getTextureRect();
	auto& scale = m_debugSprite.getScale();
	auto& newSize = transform->getSize();
	m_debugSprite.setScale( newSize.x / (texrect.width*scale.x), newSize.y / (texrect.height*scale.y) );
}

void nb::TerrainComponent::onRotationChanged( const TransformationComponent*const transform, float oldRotation )
{
	throw std::logic_error( "Cannot rotate Terrain" );
}

void TerrainComponent::init()
{
	auto entity = getEntity();

	auto transform = entity->getComponent<TransformationComponent>();
	transform->s_positionXYChanged.connect( this, &TerrainComponent::onPositionXYChanged );
	transform->s_sizeChanged.connect( this, &TerrainComponent::onSizeChanged );
	transform->s_rotationChanged.connect( this, &TerrainComponent::onRotationChanged );

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
