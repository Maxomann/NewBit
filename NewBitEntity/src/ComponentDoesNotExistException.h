#pragma once
#include "stdafx.h"

namespace nb
{
	namespace entity
	{
		namespace exception
		{
			class ComponentDoesNotExistException : public std::exception
			{
				const std::string m_message;
			public:
				ComponentDoesNotExistException( const std::string& componentTypeName );

				virtual const char* what()const override;
			};
		}
	}
}