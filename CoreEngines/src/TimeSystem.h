#pragma once
#include "stdafx.h"

namespace nb
{
	class TimeSystem : public System
	{
		sf::Clock clock;
		sf::Time frameTime;
		bool isFirstIteartion = true;

	public:
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;

		const sf::Time& getFrameTime()const;
	};
}
