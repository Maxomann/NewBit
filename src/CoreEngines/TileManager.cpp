#include "TileManager.h"
using namespace std;
using namespace sf;
using namespace nb;

const std::vector<std::string> TileManager::AUTO_CACHE_ID_COMPONENTS = { "tile", "tiles" };

void TileManager::parseFile( const std::string& path,
							 const TextureManager& textures )
{
	ifstream file( path );
	json::json fileContent;
	file >> fileContent;

	if (fileContent.is_array())
	{
		for (const auto& el : fileContent)
		{
			Tile::ID id( el.at( "id" ).get<Tile::ID>() );
			string name( el.at( "name" ).get<string>() );
			GlobalId textureId( el.at( "texture" ).get<std::string>() );
			const TextureReference* texref = textures.getTextureReference( textureId );

			tiles.push_back( Tile( move( id ),
								   move( name ),
								   move( texref ) ) );
		}
	}
	else if (fileContent.is_object())
	{
		Tile::ID id( fileContent.at( "id" ).get<Tile::ID>() );
		string name( fileContent.at( "name" ).get<string>() );
		GlobalId textureId( fileContent.at( "texture" ).get<std::string>() );
		const TextureReference* texref = textures.getTextureReference( textureId );

		tiles.push_back( Tile( move( id ),
							   move( name ),
							   move( texref ) ) );
	}
	else
		throw std::runtime_error( "TileManager::parseFile failed: fileContent is not array or object" );
}

void TileManager::init( const PackageManager& packages,
						const TextureManager& textures )
{
	for (const Package& package : packages.getLoadedPackages())
	{
		for (const auto& file : package.getLoadedMetaFiles())
		{
			auto& localId = file.getId();

			bool shouldLoad = any_of( AUTO_CACHE_ID_COMPONENTS.begin(), AUTO_CACHE_ID_COMPONENTS.end(), [&]( const std::string& el ) {
				return localId.containsComponent( el );
			} );

			if (shouldLoad)
				parseFile( file.getConnectedFilePath(), textures );
		}
	}
}

const Tile* TileManager::getTile( Tile::ID id )const
{
	auto found = find_if( tiles.begin(), tiles.end(), [&]( const Tile& el ) {
		return (el.getId() == id);
	} );

	if (found != tiles.end())
		return &(*found);
	else
		return nullptr;
}

const std::list<Tile>& nb::TileManager::getAllTiles() const
{
	return tiles;
}
