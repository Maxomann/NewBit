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
				SystemDoesNotExistException( const std::string& systemTypeName );

				virtual const char* what()const override;
			};
		}
	}
}