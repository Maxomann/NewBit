#pragma once
#include "stdafx.h"
#include "InputEngine.h"
#include "ResourceEngine.h"
#include "CameraComponent.h"
#include "GraphicsEngine.h"
#include "TransformationComponent.h"
#include "ChunkSystem.h"
#include "TileMapComponent.h"
#include "WorldLoadingGameState.h"
#include "PositionTrackerComponent.h"
#include "GraphicsEngine.h"
#include "EntityTrackerScreenGameState.h"
#include "DemoEditGameState.h"
#include "PhysicsSystem.h"
#include "TilePaintGameState.h"
#include "EntityFactories.h"
#include "PhysicsSystem.h"

namespace nb
{
	class TestGameState : public nb::GameState
	{
		GraphicsEngine* r_graphicsEngine;
		InputEngine* r_inputEngine;
		ResourceEngine* r_resourceEngine;
		ChunkSystem* r_chunkSystem;
		PhysicsSystem* r_physicsSystem;
		tgui::Gui* r_gui;

		World& world;
		Entity* camera;

		tgui::Label::Ptr fpsLabel;

		sf::Sprite m_sprite;
		Entity* m_debugEntity;

		EntityTrackerScreenGameState* r_entityTrackerScreenGameState;

		Connections m_connections;

	public:
		TestGameState( World& world, Entity* camera );

		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( GameStateManager& gameStates ) override;

		virtual void destroy( GameStateManager& gameStates ) override;

		void drawTestsprite();
	};
}
