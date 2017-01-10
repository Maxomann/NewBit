#pragma once
#include "stdafx.h"

namespace nb
{
	class TestEngine : public nb::CoreEngine
	{
		sf::RenderWindow window;
		sf::CircleShape shape;

	public:
		DLL_EXPORT TestEngine();

		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual bool update()override;

		DLL_EXPORT virtual unsigned int getId()const override;
	};
}