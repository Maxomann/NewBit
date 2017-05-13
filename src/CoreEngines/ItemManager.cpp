#include "ItemManager.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::ItemManager::parseFile( const std::string & path, const TextureManager & textures )
{
	ifstream file( path );
	json::json fileContent;
	file >> fileContent;

	if( fileContent.is_array() )
	{
		for( const auto& el : fileContent )
		{
			Item::ID id( el.at( "id" ).get<Item::ID>() );
			string name( el.at( "name" ).get<string>() );
			GlobalId textureId( el.at( "texture" ).get<std::string>() );

			addFactory( make_unique<DefaultItemFactory>( move( id ),
														 move( name ),
														 DefaultItemFactory::LABELS(),
														 move( textureId ) ) );
		}
	}
	else if( fileContent.is_object() )
	{
		Item::ID id( fileContent.at( "id" ).get<Item::ID>() );
		string name( fileContent.at( "name" ).get<string>() );
		GlobalId textureId( fileContent.at( "texture" ).get<std::string>() );

		addFactory( make_unique<DefaultItemFactory>( move( id ),
													 move( name ),
													 DefaultItemFactory::LABELS(),
													 move( textureId ) ) );
	}
	else
		throw std::runtime_error( "ItemManager::parseFile failed: fileContent is not array or object" );
}

void nb::ItemManager::init( const PackageManager & packages, const TextureManager & textures )
{
	for( const Package& package : packages.getLoadedPackages() )
	{
		for( const auto& file : package.getLoadedMetaFiles() )
		{
			auto& localId = file.getId();

			if( localId.containsComponent( "item" ) )
				parseFile( file.getConnectedFilePath(), textures );
		}
	}
}

Entity ItemManager::createItemEntity( std::unique_ptr<Item> item,
									  sf::Vector3i position )
{
	return createItemEntity( move( item ), Position( position.x,
													 position.y,
													 position.z ) );
}

Entity nb::ItemManager::createItemEntity( std::unique_ptr<Item> item, Position position )
{
	Entity entity;
	entity.addComponent<TransformationComponent>( sf::Vector2f( position.xy.x, position.xy.y ),
												  position.layer,
												  Vector2f( 32, 32 ) );
	entity.addComponent<RenderComponent>( 0 );
	entity.addComponent<SpriteComponent>( *item->getTextureReference() );

	/* Physics */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;

	unique_ptr<b2PolygonShape> shape = make_unique<b2PolygonShape>();
	auto physicsSize = 32.f * PIXEL_TO_METER * 0.5f;
	shape->SetAsBox( physicsSize, physicsSize, b2Vec2( 0.f, -physicsSize ), 0.f );

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	entity.addComponent<PhysicsComponent>( bodyDef,
										   move( shape ),
										   fixtureDef,
										   true );

	entity.addComponent<ItemComponent>( move( item ) );

	return entity;
}
