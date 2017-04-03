#include "RenderSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::RenderSystem::onEntityAdded( Entity * entity )
{
	auto renderComponent = entity->getComponent_try<RenderComponent>();

	if (renderComponent)
		m_entitiesToDraw.push_back( entity );
}

void nb::RenderSystem::onEntitiesRemoved( const std::vector<Entity*>& entities )
{
	std::vector<const Entity*> toRemove;

	for (const auto& entity : entities)
	{
		auto renderComponent = entity->getComponent_try<RenderComponent>();

		if (renderComponent)
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

void RenderSystem::init()
{
	auto world = getWorld();
	world->s_onEntityAdded.connect( this, &RenderSystem::onEntityAdded );
	world->s_onEntitiesRemoved.connect( this, &RenderSystem::onEntitiesRemoved );
};

void RenderSystem::update()
{
};

void RenderSystem::destroy()
{
};

void nb::RenderSystem::setCamerasForDrawing( std::vector<Entity*> cameras )
{
	m_camerasForDrawing = cameras;
	s_camerasForDrawingChanged.call( m_camerasForDrawing );
}

const std::vector<Entity*>& nb::RenderSystem::getCamerasForDrawing() const
{
	return m_camerasForDrawing;
}

const std::vector<Entity*>& nb::RenderSystem::getEntitiesWithRenderComponent() const
{
	return m_entitiesToDraw;
}

const std::vector<std::unique_ptr<sf::Drawable>>& nb::RenderSystem::getDebugDrawingDataForLayer( int layer )
{
	debugDrawingData.clear();
	s_collectDebugDrawingData.call( debugDrawingData, layer );
	return debugDrawingData;
}
