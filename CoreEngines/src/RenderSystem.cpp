#include "RenderSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::RenderSystem::onEntityAdded( Entity * entity )
{
	auto spriteComponent = entity->getComponent_try<SpriteComponent>();

	if (spriteComponent)
		m_entitiesToDraw.push_back( entity );
}

void nb::RenderSystem::onEntitiesRemoved( const std::vector<Entity*>& entities )
{
	std::vector<const Entity*> toRemove;

	for (const auto& entity : entities)
	{
		auto spriteComponent = entity->getComponent_try<SpriteComponent>();

		if (spriteComponent)
			toRemove.push_back( entity );
	}

	m_entitiesToDraw.erase(
		std::remove_if( m_entitiesToDraw.begin(),
						m_entitiesToDraw.end(), [&]( const Entity* el ) -> bool {
		return std::any_of( toRemove.begin(), toRemove.end(), [&]( const Entity* el2 ) -> bool {
			return (el == el2);
		} );
	} ), m_entitiesToDraw.end() );
}

void RenderSystem::init( World& world )
{
	world.s_onEntityAdded.connect_mem_fn_auto( &RenderSystem::onEntityAdded, *this );
	world.s_onEntitiesRemoved.connect_mem_fn_auto( &RenderSystem::onEntitiesRemoved, *this );
};

void RenderSystem::update( World& world )
{
	// sort sprites?

	// generate drawingData
	m_drawingData.clear();
	for (const auto& cam : m_camerasForDrawing)
	{
		std::vector<const sf::Drawable*> toDraw;
		for (const auto& el : m_entitiesToDraw)
			if (cam->getComponent<TransformationComponent>()->getLayer() == el->getComponent<TransformationComponent>()->getLayer())
				toDraw.push_back( &el->getComponent<SpriteComponent>()->getSprite() );
		m_drawingData.push_back( make_pair( &cam->getComponent<CameraComponent>()->getView(), move( toDraw ) ) );
	}
};

void RenderSystem::destroy( World& world )
{
};

void nb::RenderSystem::setCamerasForDrawing( std::vector<Entity*> cameras )
{
	m_camerasForDrawing = cameras;
}

const RenderSystem::DrawingData & nb::RenderSystem::getCurrentDrawingData() const
{
	return m_drawingData;
}
