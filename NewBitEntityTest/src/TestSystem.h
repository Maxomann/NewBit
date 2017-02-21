#include "stdafx.h"

class TestSystem : public nb::System
{
public:
	virtual void init( nb::World& world ) override;
	virtual void update( nb::World& world ) override;
	virtual void destroy( nb::World& world ) override;

	bool has_init = false;
	bool has_update = false;
};
