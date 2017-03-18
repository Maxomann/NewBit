#include "TextureReference.h"
using namespace std;

nb::tp::TextureReference::TextureReference( TextureId id,
											const sf::Texture & textureRef,
											sf::Vector2i positionOnTexture,
											sf::IntRect defaultTextureRectInDefaultCoordinates )
	: m_id( id ),
	m_textureRef( textureRef ),
	m_positionOnTexture( positionOnTexture ),
	m_defaultTextureRectInDefaultCoordinates( defaultTextureRectInDefaultCoordinates )
{}

nb::tp::TextureId nb::tp::TextureReference::getId() const
{
	return m_id;
}

const sf::Texture & nb::tp::TextureReference::getTexturePtr() const
{
	return m_textureRef;
}

sf::Vector2i nb::tp::TextureReference::getPositionOnTexture() const
{
	return m_positionOnTexture;
}

sf::IntRect nb::tp::TextureReference::tranformTextureRectToReferenceCoordinates( sf::IntRect textureRect ) const
{
	return sf::IntRect( textureRect.left + m_positionOnTexture.x,
						textureRect.top + m_positionOnTexture.y,
						textureRect.width,
						textureRect.height );
}

const sf::IntRect & nb::tp::TextureReference::getDefaultTextureRect()const
{
	return m_defaultTextureRectInDefaultCoordinates;
}

void nb::tp::TextureReference::applyToSprite( sf::Sprite & sprite ) const
{
	sprite.setTexture( m_textureRef );
	sprite.setTextureRect( tranformTextureRectToReferenceCoordinates( m_defaultTextureRectInDefaultCoordinates ) );
}
