#include "RenderSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::RenderSystem::onEntityAdded( Entity * entity )
{
	auto renderComponent = entity->getComponent_try<RenderComponent>();

	if( renderComponent )
		renderComponentsInWorld.push_back( renderComponent );
}

void nb::RenderSystem::onEntitiesRemoved( const std::vector<Entity*>& entities )
{
	std::vector<const RenderComponent*> toRemove;

	for( const auto& entity : entities )
	{
		auto renderComponent = entity->getComponent_try<RenderComponent>();

		if( renderComponent )
			toRemove.push_back( renderComponent );
	}

	renderComponentsInWorld.erase(
		std::remove_if( renderComponentsInWorld.begin(),
						renderComponentsInWorld.end(), [&] ( const RenderComponent* el ) -> bool{
		return std::any_of( toRemove.begin(), toRemove.end(), [&] ( const RenderComponent* el2 ) -> bool{
			return ( el == el2 );
		} );
	} ), renderComponentsInWorld.end() );
}

void RenderSystem::init()
{
	auto world = getWorld();
	world->s_onEntityAdded.connect( this, &RenderSystem::onEntityAdded );
	world->s_onEntitiesRemoved.connect( this, &RenderSystem::onEntitiesRemoved );
};

void RenderSystem::update()
{
	debugDrawingData.clear();
};

void RenderSystem::destroy()
{};

const std::vector<RenderComponent*>& nb::RenderSystem::getRenderComponentsInWorld() const
{
	return renderComponentsInWorld;
}

const std::vector<std::unique_ptr<sf::Drawable>>& nb::RenderSystem::getDebugDrawingDataForLayer( int layer )
{
	s_collectDebugDrawingData.call( debugDrawingData, layer );
	return debugDrawingData;
}
