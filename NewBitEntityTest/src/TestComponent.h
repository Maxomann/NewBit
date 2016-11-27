#include "stdafx.h"

class TestComponent : public nb::entity::Component
{
public:
	TestComponent();

	virtual void init( const nb::entity::Entity& entity ) override;
	virtual void destroy( const nb::entity::Entity& entity ) override;

	bool has_init = false;
};