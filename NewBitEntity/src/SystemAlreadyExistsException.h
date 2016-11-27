#pragma once
#include "stdafx.h"

namespace nb
{
	namespace entity
	{
		namespace exception
		{
			class SystemAlreadyExistsException : public std::exception
			{
				const std::string m_message;
			public:
				SystemAlreadyExistsException( const std::string& m_systemTypeName );

				virtual const char* what()const override;
			};
		}
	}
}