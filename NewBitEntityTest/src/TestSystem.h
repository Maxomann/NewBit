#include "stdafx.h"

class TestSystem : public nb::System
{
public:
	TestSystem();

	virtual void init( const nb::SystemManager& systemManager,
					   const nb::EntityManager& entityManager ) override;
	virtual void update( const nb::SystemManager& systemManager,
						 const nb::EntityManager& entityManager ) override;
	virtual void destroy( const nb::SystemManager& systemManager,
						  const nb::EntityManager& entityManager ) override;

	bool has_init = false;
	bool has_update = false;
};
