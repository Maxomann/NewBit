#pragma once
#include "stdafx.h"

namespace nb
{
	class NeedsComponent : public Component
	{
		float hunger;

	public:
		NeedsComponent();

		virtual void init() override;
		virtual void destroy() override;

		int getHunger()const;
		void setHunger( float val );
		void changeHunger( float change );

		//second parameter: old hunger
		Signal<void( const NeedsComponent*const, float )> s_hungerChanged;
	};
}
