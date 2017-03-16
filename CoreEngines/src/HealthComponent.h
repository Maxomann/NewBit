#pragma once
#include "stdafx.h"

namespace nb
{
	class HealthComponent : public Component
	{
		int m_health = 100;

	public:
		virtual void init() override;

		virtual void destroy() override;

		void damage( unsigned int amount );

		void heal( unsigned int amount );

		int getHealth()const;

		bool isDead()const;

		Signal<void( const HealthComponent*const, int )> s_onChange;
		Signal<void( const HealthComponent*const, unsigned int )> s_onDamage;
		Signal<void( const HealthComponent*const, unsigned int )> s_onHeal;
		Signal<void( const HealthComponent*const )> s_onDie;
		Signal<void( const HealthComponent*const )> s_onResurrect;
	};
}
