#include "TextureReference.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::TextureReference::TextureReference( GlobalId id,
										const sf::Texture& texture,
										const sf::IntRect defaultTextureRect )
	: m_id( id ),
	m_texture( &texture ),
	m_defaultTextureRect( defaultTextureRect )
{};

const sf::Texture& nb::TextureReference::getTexture()const
{
	return *m_texture;
};
const sf::IntRect& nb::TextureReference::getDefaultTextureRect()const
{
	return m_defaultTextureRect;
};

const nb::GlobalId& nb::TextureReference::getId() const
{
	return m_id;
}

const void nb::TextureReference::applyTextureAndDefaultTextureRectToSprite( sf::Sprite & sprite )const
{
	sprite.setTexture( getTexture() );
	sprite.setTextureRect( getDefaultTextureRect() );
}
