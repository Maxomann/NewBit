#include "TextureManager.h"
using namespace std;
using namespace sf;
using namespace nb;

const std::vector<std::string> TextureManager::AUTO_CACHE_ID_COMPONENTS = {"texture", "textures", "tex"};
const std::string TextureManager::META_ATTR_TYPE_VALUE_TEXTURE = "texture";

void nb::TextureManager::init( PackageManager& packages )
{
	for( const Package& package : packages.getLoadedPackages() )
	{
		for( const auto& file : package.getLoadedMetaFiles() )
		{
			const auto& id = package.convertLocalToGlobalId( file.getId() );
			bool shouldLoad = any_of( AUTO_CACHE_ID_COMPONENTS.begin(), AUTO_CACHE_ID_COMPONENTS.end(), [&] ( const std::string& el ){
				return id.local.containsComponent( el );
			} );
			if( !shouldLoad )
			{
				auto& data = file.getData();
				auto typeAttributes = data.find( META_ATTR_TYPE );
				if( typeAttributes != data.end() )
				{
					shouldLoad = any_of( typeAttributes->begin(), typeAttributes->end(), [&] ( const std::string& el ){
						return el == META_ATTR_TYPE_VALUE_TEXTURE;
					} );
				}
			}
			if( shouldLoad )
			{
				const auto& path = file.getConnectedFilePath();
				sf::Texture tex;
				if( !tex.loadFromFile( path ) )
					throw std::exception();
				m_textureCache.push_back( move( tex ) );
				sf::IntRect defaultTexRect( {0,0}, sf::Vector2i( m_textureCache.back().getSize() ) );
				TextureReference ref( id, m_textureCache.back(), defaultTexRect );
				auto idString = id.toString();
				m_textureReferencesByGlobalId.emplace( make_pair( move( idString ), move( ref ) ) );
			}
		}
	}
}

const TextureReference* nb::TextureManager::getTextureReference( const GlobalId& globalId )const
{
	auto found = m_textureReferencesByGlobalId.find( globalId );
	if( found != m_textureReferencesByGlobalId.end() )
		return &found->second;
	else
		return nullptr;
}
