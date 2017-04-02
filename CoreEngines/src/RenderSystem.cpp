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

/*void nb::RenderSystem::generateDrawingData()
{
	// get debug drawing data
	debugDrawingData.clear();

	// generate drawingData
	m_drawingData.clear();
	for (const auto& cam : m_camerasForDrawing)
	{
		auto camLayer = cam->getComponent<TransformationComponent>()->getLayer();
		s_collectDebugDrawingData.call( debugDrawingData, camLayer );

		std::vector<const sf::Drawable*> toDraw;
		for (const auto& el : m_entitiesToDraw)
		{
			if (camLayer == el->getComponent<TransformationComponent>()->getLayer())
			{
				const auto& renderComponentDrawingData = el->getComponent<RenderComponent>()->getDrawingData();
				toDraw.insert( toDraw.end(), renderComponentDrawingData.begin(), renderComponentDrawingData.end() );
			}
		}
		for (const auto& el : debugDrawingData)
			toDraw.push_back( el.get() );
		m_drawingData.push_back( make_pair( &cam->getComponent<CameraComponent>()->getView(), move( toDraw ) ) );
	}

	m_drawingDataIsValid = true;
}*/

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

void nb::RenderSystem::sort()
{
	// sort entitiesToDraw
	std::sort( m_entitiesToDraw.begin(), m_entitiesToDraw.end(), [&]( const Entity* lhs, const Entity* rhs ) {
		// order: z^-1,y,x
		const auto& posLhs = lhs->getComponent<TransformationComponent>()->getPositionXY();
		const auto& posRhs = rhs->getComponent<TransformationComponent>()->getPositionXY();
		const auto& zVlaueLhs = lhs->getComponent<RenderComponent>()->getZValue();
		const auto& zVlaueRhs = rhs->getComponent<RenderComponent>()->getZValue();

		if (zVlaueRhs > zVlaueLhs)
			return true;
		else if (zVlaueRhs < zVlaueLhs)
			return false;
		else if (posRhs.y > posLhs.y)
			return true;
		else if (posRhs.y < posLhs.y)
			return false;
		else if (posRhs.x > posLhs.x)
			return true;
		else
			return false;
	} );
}

const std::vector<Entity*>& nb::RenderSystem::getEntitiesWithRenderComponentSorted() const
{
	return m_entitiesToDraw;
}

const std::vector<std::unique_ptr<sf::Drawable>>& nb::RenderSystem::getDebugDrawingDataForLayer( int layer )
{
	s_collectDebugDrawingData.call( debugDrawingData, layer );
	return debugDrawingData;
}
