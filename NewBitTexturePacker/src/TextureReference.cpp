#include "TextureReference.h"
using namespace std;

nb::tp::TextureReference::TextureReference( TextureId id,
											const sf::Texture & textureRef,
											sf::Vector2i positionOnTexture,
											sf::IntRect defaultTextureRect)
	: m_id( id ),
	m_textureRef( textureRef ),
	m_positionOnTexture( positionOnTexture ),
	m_textureRect(defaultTextureRect)
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

void nb::tp::TextureReference::setTextureRect( sf::IntRect textureRect )
{
	m_textureRect = sf::IntRect( m_positionOnTexture.x + textureRect.left,
								 m_positionOnTexture.y + textureRect.top,
								 textureRect.width,
								 textureRect.height );
}

sf::IntRect nb::tp::TextureReference::getTextureRect() const
{
	return sf::IntRect( m_textureRect.left - m_positionOnTexture.x,
						m_textureRect.top - m_positionOnTexture.y,
						m_textureRect.width,
						m_textureRect.height );
}

void nb::tp::TextureReference::applyToSprite( sf::Sprite & sprite ) const
{
	sprite.setTexture( m_textureRef );
	sprite.setTextureRect( m_textureRect );
}