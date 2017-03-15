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
	auto entity = getEntity();

	auto transform = entity->getComponent<TransformationComponent>();
	transform->s_positionXYChanged.connect( this, &SpriteComponent::onPositionXYChanged );
	transform->s_sizeChanged.connect( this, &SpriteComponent::onSizeChanged );
	transform->s_rotationChanged.connect( this, &SpriteComponent::onRotationChanged );

	auto render = entity->getComponent<RenderComponent>();
	render->addDrawable( &m_sprite );
}

void nb::SpriteComponent::destroy()
{
}

void nb::SpriteComponent::setTexture( const sf::Texture & texture )
{
	m_sprite.setTexture( texture, true );
	auto& size = texture.getSize();
	m_sprite.setOrigin( static_cast<float>(size.x) / 2.f, static_cast<float>(size.y) );
}

void nb::SpriteComponent::setTexture( const TextureReference & texture )
{
	texture.applyTextureAndDefaultTextureRectToSprite( m_sprite );
	auto& defaultRect = texture.getDefaultTextureRect();
	m_sprite.setOrigin( static_cast<float>(defaultRect.width) / 2.f,
						static_cast<float>(defaultRect.height) );
}

const sf::Sprite & nb::SpriteComponent::getSprite() const
{
	return m_sprite;
}
