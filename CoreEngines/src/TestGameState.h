#pragma once
#include "stdafx.h"
#include "InputEngine.h"
#include "ResourceEngine.h"
#include "CameraComponent.h"
#include "GraphicsEngine.h"
#include "TransformationComponent.h"
#include "ChunkSystem.h"

namespace nb
{
	class TestGameState : public nb::GameState
	{
		GraphicsEngine* r_graphicsEngine;
		InputEngine* r_inputEngine;
		ResourceEngine* r_resourceEngine;

		sf::Texture m_texture;
		sf::Texture m_texture2;
		sf::Texture m_texture_grass;
		sf::Texture m_texture_sand;

		sf::Sprite m_sprite;
		Entity* m_debugEntity;
		Entity* m_camera;

		void addALotOfEntities( const CoreRef& core );

	public:
		DLL_EXPORT virtual void init() override;

		DLL_EXPORT virtual void destroy() override;

		DLL_EXPORT virtual bool shouldDestroy() override;

		void drawTestsprite();
	};
}
