#include "PackedTexture.h"
using namespace std;

void nb::tp::PackedTexture::m_throwIfGenerated()
{
	if ( m_isGenerated )
		throw exception::PackedTextureGenerationStateException( m_id, m_isGenerated );
}

void nb::tp::PackedTexture::m_throwIfNotGenerated()
{
	if ( !m_isGenerated )
		throw exception::PackedTextureGenerationStateException( m_id, m_isGenerated );
}

nb::tp::PackedTexture::PackedTexture( PackedTextureId id )
	:m_id( id )
{}

nb::tp::PackedTextureId nb::tp::PackedTexture::getId() const
{
	return m_id;
}

void nb::tp::PackedTexture::addTexture( TextureId textureId, const sf::Image& image )
{
	m_throwIfGenerated();

	sf::Texture texture;
	texture.loadFromImage( image );
	addTexture( textureId, texture );
}

void nb::tp::PackedTexture::addTexture( TextureId textureId, const sf::Texture & texture )
{
	m_throwIfGenerated();

	m_subTextures.emplace_back( textureId, texture );
}

void nb::tp::PackedTexture::generate()
{
	m_throwIfGenerated();

	// check for dublicates
	sort( m_subTextures.begin(), m_subTextures.end(), []( const std::pair<TextureId, sf::Texture>& lhs,
														  const std::pair<TextureId, sf::Texture>& rhs ) {
		return lhs.first < rhs.first;
	} );
	if ( unique( m_subTextures.begin(), m_subTextures.end() ) != m_subTextures.end() )
		;//throw here

	// generate
}