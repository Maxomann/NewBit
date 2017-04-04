#pragma once
#include "stdafx.h"

namespace nb
{
	class NeedsComponent : public Component
	{
		float hunger = 100;

	public:
		virtual void init() override;
		virtual void destroy() override;

		int getHunger()const;
		void setHunger( float val );
		void changeHunger( float change );
	};
}
