#pragma once
#include "stdafx.h"
#include "id.h"
#include "GraphicsEngine.h"

namespace nb
{
	class InputEngine : public CoreEngine
	{
		GraphicsEngine* r_graphicsEngine;

		std::map<sf::Keyboard::Key, bool> pressedKeys;
		std::map<sf::Mouse::Button, bool> isMouseButtonPressed;
		sf::Vector2i mousePosition;

	public:
		virtual void init( const CoreEngineManager& coreEngines ) override;

		virtual bool update() override;

		void onSfEvent( const sf::Event& event );

		bool isKeyPressed( sf::Keyboard::Key key )const;

		std::map<sf::Keyboard::Key, Signal<void()>> s_whileKeyPressed; // called every frame
		std::map<sf::Keyboard::Key, Signal<void()>> s_onKeyPressed; // NOT called every frame
		std::map<sf::Keyboard::Key, Signal<void()>> s_onKeyReleased;

		std::map<sf::Mouse::Button, Signal<void( sf::Vector2i )>> s_onMouseButtonPressed; // NOT called every frame
		std::map<sf::Mouse::Button, Signal<void( sf::Vector2i )>> s_onMouseButtonPressedInWindow; // NOT called every frame

		std::map<sf::Mouse::Button, Signal<void( sf::Vector2i )>> s_onMouseButtonReleased; // NOT called every frame
		std::map<sf::Mouse::Button, Signal<void( sf::Vector2i )>> s_onMouseButtonReleasedInWindow; // NOT called every frame

		std::map<sf::Mouse::Button, Signal<void( sf::Vector2i )>> s_whileMouseButtonPressed; // called every frame
		std::map<sf::Mouse::Button, Signal<void( sf::Vector2i )>> s_whileMouseButtonPressedInWindow; // called every frame
	};
}
