#pragma once
#include "stdafx.h"

namespace nb
{
	class TimeSystem : public System
	{
		sf::Time timestep;

	public:
		virtual void init() override;
		virtual void update() override;
		virtual void destroy() override;

		void updateTimestep( const sf::Time& step );

		const sf::Time& getTimestep()const;
	};
}
