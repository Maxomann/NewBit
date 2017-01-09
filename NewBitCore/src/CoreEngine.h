#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngine
	{
	public:
		DLL_EXPORT virtual ~CoreEngine() = default;

		DLL_EXPORT virtual unsigned int getId()const = 0;
	};
}