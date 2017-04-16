#include "EntityFactories.h"
#include "ChunkSystem.h"
#include "ResourceEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

Entity nb::createHuman( const CoreEngineManager& engines, sf::Vector3i position )
{
	Entity entity;
	entity.addComponent<TransformationComponent>( sf::Vector2i( position.x, position.y ),
												  position.z,
												  Vector2f( 32, 64 ) );
	entity.addComponent<RenderComponent>( 0 );
	entity.addComponent<SpriteComponent>( *engines.getEngine<ResourceEngine>()->textures.getTextureReference( "default:texture:player" ) );
	entity.addComponent<HealthComponent>( 200, 100 );

	/* Physics */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;
	bodyDef.fixedRotation = true;

	unique_ptr<b2PolygonShape> shape = make_unique<b2PolygonShape>();
	shape->SetAsBox( 0.3f, 0.3f, b2Vec2( 0.f, -0.3f ), 0.f );

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	entity.addComponent<PhysicsComponent>( bodyDef,
										   move( shape ),
										   fixtureDef );

	entity.addComponent<NeedsComponent>();
	entity.addComponent<InventoryComponent>();

	return entity;
}

Entity nb::createTilemapChunk( const CoreEngineManager & engines, sf::Vector3i positionInChunks, std::vector<std::vector<const Tile*>> tiles )
{
	Entity terrain;
	terrain.addComponent<TransformationComponent>(
		Vector2i( ChunkSystem::CHUNK_SIZE_IN_PIXEL * positionInChunks.x,
				  ChunkSystem::CHUNK_SIZE_IN_PIXEL * positionInChunks.y ),
		positionInChunks.z,
		Vector2f( ChunkSystem::CHUNK_SIZE_IN_PIXEL,
				  ChunkSystem::CHUNK_SIZE_IN_PIXEL )
		);
	terrain.addComponent<RenderComponent>( -10 );

	auto terrainComp = terrain.addComponent<TileMapComponent>( move( tiles ) );

	return terrain;
}

Entity nb::createTree( const CoreEngineManager & engines, sf::Vector3i position )
{
	Entity entity;
	entity.addComponent<TransformationComponent>( sf::Vector2i( position.x, position.y ),
												  position.z,
												  Vector2f( 48 * 2, 64 * 2 ) );
	entity.addComponent<RenderComponent>( 0 );
	entity.addComponent<SpriteComponent>( *engines.getEngine<ResourceEngine>()->textures.getTextureReference( "default:texture:object_tree" ) );
	/* Physics */
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	unique_ptr<b2PolygonShape> shape = make_unique<b2PolygonShape>();
	shape->SetAsBox( 0.3f, 0.3f, b2Vec2( 0.f, -0.3f ), 0.f );

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	entity.addComponent<PhysicsComponent>( bodyDef,
										   move( shape ),
										   fixtureDef );

	return entity;
}

TreeFactory::TreeFactory()
	: EntityFactory( 0,
					 "Tree",
					 {} )
{
}

Entity TreeFactory::create( const ResourceEngine& resources )const
{
	Entity entity;
	entity.addComponent<TransformationComponent>( sf::Vector2i( 0, 0 ),
												  0,
												  Vector2f( 48 * 2, 64 * 2 ) );
	entity.addComponent<RenderComponent>( 0 );
	entity.addComponent<SpriteComponent>( *resources.textures.getTextureReference( "default:texture:object_tree" ) );
	/* Physics */
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	unique_ptr<b2PolygonShape> shape = make_unique<b2PolygonShape>();
	shape->SetAsBox( 0.3f, 0.3f, b2Vec2( 0.f, -0.3f ), 0.f );

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	entity.addComponent<PhysicsComponent>( bodyDef,
										   move( shape ),
										   fixtureDef );

	return entity;
}

ItemWoodFactory::ItemWoodFactory()
	: EntityFactory( 10'000,
					 "Item: Wood",
					 { "item" } )
{
}

Entity ItemWoodFactory::create( const ResourceEngine& resources )const
{
	const auto& item = resources.items.getItem( 0 );

	Entity entity;
	entity.addComponent<TransformationComponent>( sf::Vector2i( 0, 0 ),
												  0,
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

	entity.addComponent<ItemComponent>( item );

	return entity;
}
