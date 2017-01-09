#pragma once
#include "stdafx.h"
#include "CoreEngine.h"

namespace nb
{
	class CoreEngineManager
	{
		using connectFunctionType = void( CoreEngineManager* );

		std::unordered_map<unsigned int, std::unique_ptr<CoreEngine>> m_engines;

	public:
		DLL_EXPORT void loadFromFolder( std::string pathToFolder );

		DLL_EXPORT void addEngine( std::unique_ptr<CoreEngine>&& ptr );
		DLL_EXPORT CoreEngine* getEngine( const unsigned int id )const;
	};
}