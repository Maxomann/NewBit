#pragma once
#include "stdafx.h"

namespace nb
{
	namespace entity
	{
		namespace exception
		{
			class EntityDoesNotExistException : public std::exception
			{
			public:
				DLL_EXPORT virtual const char* what()const override;
			};
		}
	}
}