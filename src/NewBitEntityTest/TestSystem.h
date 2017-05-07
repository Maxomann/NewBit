#include "stdafx.h"

class TestSystem : public nb::System
{
public:
	virtual void init() override;
	virtual void() override;
	virtual void destroy() override;

	bool has_init = false;
	bool has_update = false;
};
