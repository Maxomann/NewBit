#pragma once
#include "stdafx.h"
#include "InputEngine.h"
#include "ResourceEngine.h"
#include "CameraComponent.h"
#include "GraphicsEngine.h"
#include "TransformationComponent.h"

namespace nb
{
	class TestGameState : public nb::GameState, public Trackable
	{
		GraphicsEngine* r_graphicsEngine;
		InputEngine* r_inputEngine;
		ResourceEngine* r_resourceEngine;

		sf::Texture m_texture;
		sf::Texture m_texture2;

		sf::Sprite m_sprite;
		Entity* m_debugEntity;
		Entity* m_camera;

	public:
		DLL_EXPORT virtual void init( const CoreRef& coreRefs ) override;

		DLL_EXPORT virtual void destroy( const CoreRef& coreRefs ) override;

		DLL_EXPORT virtual bool shouldDestroy() override;

		void drawTestsprite();
	};
}
