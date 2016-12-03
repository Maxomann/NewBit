#include "TextureReference.h"
using namespace std;

nb::tp::TextureReference::TextureReference( TextureId id,
											sf::Texture & textureRef,
											sf::Vector2i positionOnTexture )
	: m_id( id ),
	m_textureRef( textureRef ),
	m_positionOnTexture( positionOnTexture )
{}

nb::tp::TextureId nb::tp::TextureReference::getId() const
{
	return m_id;
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