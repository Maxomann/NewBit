#pragma once
#include "stdafx.h"
#include "InputEngine.h"
#include "ResourceEngine.h"
#include "CameraComponent.h"
#include "GraphicsEngine.h"
#include "TransformationComponent.h"
#include "ChunkSystem.h"
#include "TerrainComponent.h"
#include "WorldLoadingGameState.h"
#include "PositionTrackerComponent.h"

namespace nb
{
	class TestGameState : public nb::GameState
	{
		const CoreRef* r_core;
		GraphicsEngine* r_graphicsEngine;
		InputEngine* r_inputEngine;
		ResourceEngine* r_resourceEngine;
		ChunkSystem* r_chunkSystem;
		WorldGenerationEngine* r_worldGenerationEngine;

		sf::Sprite m_sprite;
		Entity* m_debugEntity;
		Entity* m_camera;

		WorldLoadingGameState* r_worldLoadingGameState;

		void addALotOfEntities();
		void addSomeTerrain();

		Connections m_connections;

	public:
		DLL_EXPORT virtual void init() override;

		DLL_EXPORT virtual void update() override;

		DLL_EXPORT virtual void destroy() override;

		DLL_EXPORT virtual bool shouldDestroy() override;

		void drawTestsprite();
	};
}
