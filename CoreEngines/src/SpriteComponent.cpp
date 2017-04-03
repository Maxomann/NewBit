#include "SpriteComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::SpriteComponent::setSize( sf::Vector2f newSize )
{
	auto& texrect = m_sprite.getTextureRect();
	auto& scale = m_sprite.getScale();

	Vector2f spritesOldSize;
	spritesOldSize.x = (static_cast<float>(texrect.width)*scale.x);
	spritesOldSize.y = (static_cast<float>(texrect.height)*scale.y);

	m_sprite.setScale( newSize.x / spritesOldSize.x, newSize.y / spritesOldSize.y );
	calculateGlobalBounds();
}

void nb::SpriteComponent::calculateGlobalBounds()
{
	globalBounds = m_sprite.getGlobalBounds();
}

nb::SpriteComponent::SpriteComponent( const sf::Texture & texture )
{
	setTexture( texture );
}

nb::SpriteComponent::SpriteComponent( const TextureReference & texture )
{
	setTexture( texture );
}

void nb::SpriteComponent::init()
{
	auto entity = getEntity();

	auto transform = entity->getComponent<TransformationComponent>();
	//default values
	m_sprite.setPosition( Vector2f( transform->getPositionXY() ) );
	setSize( transform->getSize() );
	m_sprite.setRotation( transform->getRotation() );

	//connections
	transform->s_positionXYChanged.connect( [&]( const TransformationComponent*const transform,
												 sf::Vector2i oldPositionXY ) {
		m_sprite.setPosition( Vector2f( transform->getPositionXY() ) );
		calculateGlobalBounds();
	} );
	transform->s_sizeChanged.connect( [&]( const TransformationComponent*const transform,
										   sf::Vector2f oldSize ) {
		setSize( transform->getSize() );
	} );
	transform->s_rotationChanged.connect( [&]( const TransformationComponent*const transform,
											   float oldRotation ) {
		m_sprite.setRotation( transform->getRotation() );
		calculateGlobalBounds();
	} );

	calculateGlobalBounds();

	// add drawable
	auto render = entity->getComponent<RenderComponent>();
	render->addDrawable( &m_sprite, &globalBounds );
}

void nb::SpriteComponent::destroy()
{
}

void nb::SpriteComponent::setTexture( const sf::Texture & texture )
{
	m_sprite.setTexture( texture, true );
	auto& size = texture.getSize();
	m_sprite.setOrigin( static_cast<float>(size.x) / 2.f, static_cast<float>(size.y) );
	calculateGlobalBounds();
}

void nb::SpriteComponent::setTexture( const TextureReference & texture )
{
	texture.applyTextureAndDefaultTextureRectToSprite( m_sprite );
	auto& defaultRect = texture.getDefaultTextureRect();
	m_sprite.setOrigin( static_cast<float>(defaultRect.width) / 2.f,
						static_cast<float>(defaultRect.height) );
	calculateGlobalBounds();
}

const sf::Sprite & nb::SpriteComponent::getSprite() const
{
	return m_sprite;
}
