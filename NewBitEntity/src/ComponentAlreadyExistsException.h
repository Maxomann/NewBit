#pragma once
#include "stdafx.h"

namespace nb
{
	namespace entity
	{
		namespace exception
		{
			class ComponentAlreadyExistsException : public std::exception
			{
				const std::string m_message;
			public:
				DLL_EXPORT ComponentAlreadyExistsException( const std::string& componentTypeName );

				DLL_EXPORT virtual const char* what()const override;
			};
		}
	}
}