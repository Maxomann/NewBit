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
				ComponentAlreadyExistsException( const std::string& componentTypeName );

				virtual const char* what()const override;
			};
		}
	}
}