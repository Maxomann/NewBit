#include "stdafx.h"

class TestComponent : public nb::Component
{
public:
	virtual void init() override;
	virtual void destroy() override;

	bool has_init = false;
};
