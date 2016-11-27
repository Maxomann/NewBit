#include "stdafx.h"

class TestSystem : public nb::entity::System
{
public:
	TestSystem();

	virtual void init( const nb::entity::SystemManager& systemManager, const nb::entity::EntityManager& entityManager ) override;
	virtual void update( const nb::entity::SystemManager& systemManager, const nb::entity::EntityManager& entityManager ) override;
	virtual void destroy( const nb::entity::SystemManager& systemManager, const nb::entity::EntityManager& entityManager ) override;

	bool has_init = false;
	bool has_update = false;
};