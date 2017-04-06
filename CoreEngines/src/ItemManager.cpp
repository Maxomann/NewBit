#include "ItemManager.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ItemManager::parseFile( const std::string & path, const TextureManager & textures )
{
	ifstream file( path );
	json::json fileContent;
	file >> fileContent;

	if (fileContent.is_array())
	{
		for (const auto& el : fileContent)
		{
			Item::ID id( el.at( "id" ).get<Item::ID>() );
			string name( el.at( "name" ).get<string>() );
			GlobalId textureId( el.at( "texture" ).get<std::string>() );
			const TextureReference* texref = textures.getTextureReference( textureId );

			items.push_back( Item( move( id ),
								   move( name ),
								   move( texref ) ) );
			cout << items.front().getName() << endl;
		}
	}
	else if (fileContent.is_object())
	{
		Item::ID id( fileContent.at( "id" ).get<Item::ID>() );
		string name( fileContent.at( "name" ).get<string>() );
		GlobalId textureId( fileContent.at( "texture" ).get<std::string>() );
		const TextureReference* texref = textures.getTextureReference( textureId );

		items.push_back( Item( move( id ),
							   move( name ),
							   move( texref ) ) );
	}
	else
		throw std::runtime_error( "ItemManager::parseFile failed: fileContent is not array or object" );
}

void nb::ItemManager::init( const PackageManager & packages, const TextureManager & textures )
{
	for (const Package& package : packages.getLoadedPackages())
	{
		for (const auto& file : package.getLoadedMetaFiles())
		{
			auto& localId = file.getId();

			if (localId.containsComponent( "item" ))
				parseFile( file.getConnectedFilePath(), textures );
		}
	}
}

const Item * nb::ItemManager::getItem( Item::ID id ) const
{
	auto found = find_if( items.begin(), items.end(), [&]( const Item& el ) {
		return (el.getId() == id);
	} );

	if (found != items.end())
		return &(*found);
	else
		return nullptr;
}

const std::list<Item>& nb::ItemManager::getAllItems() const
{
	return items;
}
