#include "RenderSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::RenderSystem::onEntityAdded( Entity * entity )
{
	auto spriteComponent = entity->getComponent_try<SpriteComponent>();

	if (spriteComponent)
		m_spriteComponentsToDraw.push_back( spriteComponent );
}

void nb::RenderSystem::onEntitiesRemoved( const std::vector<Entity*>& entities )
{
	std::vector<const SpriteComponent*> toRemove;

	for (const auto& entity : entities)
	{
		auto spriteComponent = entity->getComponent_try<SpriteComponent>();

		if (spriteComponent)
			toRemove.push_back( spriteComponent );
	}

	m_spriteComponentsToDraw.erase(
		std::remove_if( m_spriteComponentsToDraw.begin(),
						m_spriteComponentsToDraw.end(), [&]( const SpriteComponent* el ) -> bool {
		return std::any_of( toRemove.begin(), toRemove.end(), [&]( const SpriteComponent* el2 ) -> bool {
			return (el == el2);
		} );
	} ), m_spriteComponentsToDraw.end() );
}

void RenderSystem::init( World& world )
{
	world.s_onEntityAdded.connect_mem_fn_auto( &RenderSystem::onEntityAdded, *this );
	world.s_onEntitiesRemoved.connect_mem_fn_auto( &RenderSystem::onEntitiesRemoved, *this );
};
void RenderSystem::update( World& world )
{
	// sort sprites?
};
void RenderSystem::destroy( World& world )
{
};

const std::vector<SpriteComponent*>& RenderSystem::getSpriteComponentsToDraw()const
{
	return m_spriteComponentsToDraw;
};
