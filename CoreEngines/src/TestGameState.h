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

namespace nb
{
	class TestGameState : public nb::GameState
	{
		const CoreRef* r_core;
		GraphicsEngine* r_graphicsEngine;
		InputEngine* r_inputEngine;
		ResourceEngine* r_resourceEngine;

		sf::Sprite m_sprite;
		Entity* m_debugEntity;
		Entity* m_camera;

		void addALotOfEntities();
		void addSomeTerrain();

	public:
		DLL_EXPORT virtual void init() override;

		DLL_EXPORT virtual void destroy() override;

		DLL_EXPORT virtual bool shouldDestroy() override;

		void drawTestsprite();
	};
}
