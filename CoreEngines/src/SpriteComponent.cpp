#include "SpriteComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::SpriteComponent::onPositionXYChanged( const TransformationComponent*const transform, sf::Vector2i oldPositionXY )
{
	m_sprite.setPosition( Vector2f( transform->getPositionXY() ) );
}

void nb::SpriteComponent::onSizeChanged( const TransformationComponent*const transform, sf::Vector2u oldSize )
{
	auto& texrect = m_sprite.getTextureRect();
	auto& scale = m_sprite.getScale();
	auto& newSize = transform->getSize();
	m_sprite.setScale( newSize.x / (texrect.width*scale.x), newSize.y / (texrect.height*scale.y) );
}

void nb::SpriteComponent::onRotationChanged( const TransformationComponent*const transform, float oldRotation )
{
	m_sprite.setRotation( transform->getRotation() );
}

void nb::SpriteComponent::init()
{
	auto transform = getEntity()->getComponent<TransformationComponent>();
	transform->s_positionXYChanged.connect_mem_fn_auto( &SpriteComponent::onPositionXYChanged, *this );
	transform->s_sizeChanged.connect_mem_fn_auto( &SpriteComponent::onSizeChanged, *this );
	transform->s_rotationChanged.connect_mem_fn_auto( &SpriteComponent::onRotationChanged, *this );
}

void nb::SpriteComponent::destroy()
{
}

int nb::SpriteComponent::getZValue() const
{
	return m_zValue;
}

void nb::SpriteComponent::setZValue( int zValue )
{
	m_zValue = zValue;
}

void nb::SpriteComponent::setTexture( const sf::Texture & texture )
{
	m_sprite.setTexture( texture );
}

const sf::Sprite & nb::SpriteComponent::getSprite() const
{
	return m_sprite;
}
