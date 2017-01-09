#pragma once
#include "stdafx.h"

namespace nb
{
	class TestEngine : public nb::CoreEngine
	{
	public:
		DLL_EXPORT TestEngine();

		DLL_EXPORT virtual unsigned int getId()const;
	};
}