#pragma once
#include "stdafx.h"

namespace nb
{
	class NeedsComponent : public Component
	{
		float hunger = 100.f;
		float thirst = 100.f;
		float energy = 100.f;

		const float baseHungerRate = 0.00001f;
		const float baseThirstRate = 0.00002f;
		const float baseEnergyRate = 0.0000005f;

	public:
		NeedsComponent();

		virtual void init() override;

		void changeValuesOverTime( const sf::Time& time );

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
