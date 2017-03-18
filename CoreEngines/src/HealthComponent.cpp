#include "HealthComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::HealthComponent::init()
{
}

void nb::HealthComponent::destroy()
{
}

void nb::HealthComponent::damage( unsigned int amount )
{
	bool wasDead = isDead();
	m_health -= amount;
	s_onChange.call( this, -1 * static_cast<int>(amount) );
	s_onDamage.call( this, amount );
	if (m_health <= 0)
	{
		m_health = 0;
		if (!wasDead)
			s_onDie.call( this );
	}
}

void nb::HealthComponent::heal( unsigned int amount )
{
	bool wasDead = isDead();
	m_health += amount;
	s_onChange.call( this, amount );
	s_onHeal.call( this, amount );
	if (wasDead && m_health > 0)
		s_onResurrect.call( this );
}

int nb::HealthComponent::getHealth() const
{
	return m_health;
}

bool nb::HealthComponent::isDead() const
{
	return (m_health <= 0);
}
