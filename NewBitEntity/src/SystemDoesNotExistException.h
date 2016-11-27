#pragma once
#include "stdafx.h"

namespace nb
{
	namespace entity
	{
		namespace exception
		{
			class SystemDoesNotExistException : public std::exception
			{
				const std::string m_message;
			public:
				DLL_EXPORT SystemDoesNotExistException( const std::string& systemTypeName );

				DLL_EXPORT virtual const char* what()const override;
			};
		}
	}
}