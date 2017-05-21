#include "HealthComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::HealthComponent::HealthComponent( int maxHealth, int initialHealth )
	: m_maxHealth( maxHealth ),
	m_health( static_cast<float>( initialHealth ) )
{}

void nb::HealthComponent::init()
{}

void nb::HealthComponent::damage( float amount )
{
	amount = abs( amount );

	const float maxAmount = m_health;
	if( amount > maxAmount )
		amount = m_health;

	bool wasDead = isDead();
	m_health -= amount;

	s_onChange.call( this, -1.f * amount );
	s_onDamage.call( this, amount );

	if( m_health <= 0 )
	{
		m_health = 0;
		if( !wasDead )
			s_onDie.call( this );
	}
}

void nb::HealthComponent::heal( float amount )
{
	amount = abs( amount );

	const float maxAmount = m_maxHealth - m_health;
	if( amount > maxAmount )
		amount = maxAmount;

	bool wasDead = isDead();
	m_health += amount;
	s_onChange.call( this, amount );
	s_onHeal.call( this, amount );
	if( wasDead && m_health > 0 )
		s_onResurrect.call( this );
}

float nb::HealthComponent::getHealth() const
{
	return m_health;
}

int nb::HealthComponent::getMaxHealth() const
{
	return m_maxHealth;
}

bool nb::HealthComponent::isDead() const
{
	return ( m_health <= 0 );
}
