#pragma once
#include "stdafx.h"

namespace nb
{
	class HealthComponent : public Component
	{
		const int m_maxHealth;
		float m_health;

	public:
		HealthComponent( int maxHealth,
						 int initialHealth );

		virtual void init() override;

		virtual void destroy() override;

		void damage( float amount );

		void heal( float amount );

		int getHealth()const;
		int getMaxHealth()const;

		bool isDead()const;

		Signal<void( const HealthComponent*const, int )> s_onChange;
		Signal<void( const HealthComponent*const, float )> s_onDamage;
		Signal<void( const HealthComponent*const, float )> s_onHeal;
		Signal<void( const HealthComponent*const )> s_onDie;
		Signal<void( const HealthComponent*const )> s_onResurrect;
	};
}
