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

Entity ItemManager::createItemEntity( const Item* item,
									  sf::Vector3i position )
{
	Entity entity;
	entity.addComponent<TransformationComponent>( sf::Vector2i( position.x, position.y ),
												  position.z,
												  Vector2f( 16, 16 ) );
	entity.addComponent<RenderComponent>( 0 );
	entity.addComponent<SpriteComponent>( *item->getTextureReference() );

	/* Physics */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;

	unique_ptr<b2PolygonShape> shape = make_unique<b2PolygonShape>();
	auto physicsSize = 16.f * PIXEL_TO_METER * 0.5f;
	shape->SetAsBox( physicsSize, physicsSize, b2Vec2( 0.f, -physicsSize ), 0.f );

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	entity.addComponent<PhysicsComponent>( bodyDef,
										   move( shape ),
										   fixtureDef );

	entity.addComponent<ItemComponent>( item );

	return entity;
}
