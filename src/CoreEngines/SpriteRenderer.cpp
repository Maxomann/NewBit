#include "SpriteRenderer.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::SpriteRenderer::setSize( sf::Vector2f newSize )
{
	auto& texrect = m_sprite.getTextureRect();
	auto& scale = m_sprite.getScale();

	Vector2f spritesOldSize;
	spritesOldSize.x = ( static_cast<float>( texrect.width )*scale.x );
	spritesOldSize.y = ( static_cast<float>( texrect.height )*scale.y );

	m_sprite.setScale( newSize.x / spritesOldSize.x, newSize.y / spritesOldSize.y );
	calculateGlobalBounds();
}

void nb::SpriteRenderer::calculateGlobalBounds()
{
	globalBounds = m_sprite.getGlobalBounds();
}

nb::SpriteRenderer::SpriteRenderer( const sf::Texture & texture )
{
	setTexture( texture );
}

nb::SpriteRenderer::SpriteRenderer( const TextureReference & texture )
{
	setTexture( texture );
}

void nb::SpriteRenderer::init( const Entity * entity )
{
	auto transform = entity->getComponent<TransformationComponent>();
	//default values
	m_sprite.setPosition( Vector2f( transform->getPositionXY() ) );
	setSize( transform->getSize() );
	m_sprite.setRotation( transform->getRotation() );

	//connections
	transform->s_positionXYChanged.connect( [&] ( const TransformationComponent*const transform,
												  const sf::Vector2f& oldPositionXY ){
		m_sprite.setPosition( transform->getPositionXY() );
		calculateGlobalBounds();
	} );
	transform->s_sizeChanged.connect( [&] ( const TransformationComponent*const transform,
											sf::Vector2f oldSize ){
		setSize( transform->getSize() );
	} );
	transform->s_rotationChanged.connect( [&] ( const TransformationComponent*const transform,
												float oldRotation ){
		m_sprite.setRotation( transform->getRotation() );
		calculateGlobalBounds();
	} );

	calculateGlobalBounds();
}

const sf::FloatRect & nb::SpriteRenderer::getGlobalBounds() const
{
	return globalBounds;
}

void nb::SpriteRenderer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	target.draw( m_sprite, states );
}

void nb::SpriteRenderer::setTexture( const sf::Texture & texture )
{
	m_sprite.setTexture( texture, true );
	const auto& size = texture.getSize();
	m_sprite.setOrigin( static_cast<float>( size.x ) / 2.f, static_cast<float>( size.y ) );
	calculateGlobalBounds();
}

void nb::SpriteRenderer::setTexture( const TextureReference & texture )
{
	texture.applyTextureAndDefaultTextureRectToSprite( m_sprite );
	auto& defaultRect = texture.getDefaultTextureRect();
	m_sprite.setOrigin( static_cast<float>( defaultRect.width ) / 2.f,
						static_cast<float>( defaultRect.height ) );
	calculateGlobalBounds();
}

const sf::Sprite & nb::SpriteRenderer::getSprite() const
{
	return m_sprite;
}
