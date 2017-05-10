#pragma once
#include "stdafx.h"

namespace nb
{
	class NeedsComponent : public Component
	{
		float hunger;
		float thirst;
		float energy;

	public:
		NeedsComponent();

		virtual void init() override;

		float getHunger()const;
		void setHunger( float val );
		void changeHunger( float change );

		float getThirst()const;
		void setThirst( float val );
		void changeThirst( float change );

		float getEnergy()const;
		void setEnergy( float val );
		void changeEnergy( float change );

		//second parameter: old hunger
		Signal<void( const NeedsComponent*const, float )> s_hungerChanged;
		Signal<void( const NeedsComponent*const, float )> s_thirstChanged;
		Signal<void( const NeedsComponent*const, float )> s_energyChanged;
	};
}
