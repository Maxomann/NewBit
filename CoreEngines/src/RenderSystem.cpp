#include "RenderSystem.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::RenderSystem::onEntityAdded( Entity * entity )
{
	auto renderComponent = entity->getComponent_try<RenderComponent>();

	if (renderComponent)
		m_entitiesToDraw.push_back( entity );

	m_drawingDataIsValid = false;
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

	m_drawingDataIsValid = false;
}

void nb::RenderSystem::generateDrawingData()
{
	// get debug drawing data
	debugDrawingData.clear();
	s_collectDebugDrawingData.call( debugDrawingData );

	// sort entitiesToDraw
	std::sort( m_entitiesToDraw.begin(), m_entitiesToDraw.end(), [&]( const Entity* lhs, const Entity* rhs ) {
		// order: z^-1,y,x
		auto posLhs = lhs->getComponent<TransformationComponent>()->getPositionXY();
		auto posRhs = rhs->getComponent<TransformationComponent>()->getPositionXY();
		auto zVlaueLhs = lhs->getComponent<RenderComponent>()->getZValue();
		auto zVlaueRhs = rhs->getComponent<RenderComponent>()->getZValue();

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

	// generate drawingData
	m_drawingData.clear();
	for (const auto& cam : m_camerasForDrawing)
	{
		std::vector<const sf::Drawable*> toDraw;
		for (const auto& el : m_entitiesToDraw)
		{
			if (cam->getComponent<TransformationComponent>()->getLayer() == el->getComponent<TransformationComponent>()->getLayer())
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
}

void RenderSystem::init()
{
	auto world = getWorld();
	world->s_onEntityAdded.connect( this, &RenderSystem::onEntityAdded );
	world->s_onEntitiesRemoved.connect( this, &RenderSystem::onEntitiesRemoved );
};

void RenderSystem::update()
{
	m_drawingDataIsValid = false;
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

const RenderSystem::DrawingData & nb::RenderSystem::getCurrentDrawingData()
{
	if (!m_drawingDataIsValid)
		generateDrawingData();

	return m_drawingData;
}
