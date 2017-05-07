#pragma once
#include "stdafx.h"
#include "CoreEngine.h"

namespace nb
{
	class CoreEngineManager
	{
		std::unordered_map<std::type_index, std::unique_ptr<CoreEngine>> m_engines;
		std::vector<CoreEngine*> m_enginesVector;

	public:
		// T must implement nb::CoreEngine interface
		template<class T>
		void addEngine()
		{
			std::unique_ptr<CoreEngine> ptr = std::make_unique<T>();

			auto emplaceRetVal = m_engines.emplace(
				std::make_pair<std::type_index, unique_ptr<CoreEngine>>( std::type_index( typeid( T ) ),
																		 move( ptr ) ) );
			if( !emplaceRetVal.second )
				throw std::exception();
			m_enginesVector.push_back( emplaceRetVal.first->second.get() );
		};

		// thread safe, after initEngines() has been called
		template<class T>
		T* getEngine()const
		{
			return static_cast<T*>( m_engines.at( std::type_index( typeid( T ) ) ).get() );
		};

		// all engines must have been loaded before calling this
		// loading engines afterwards results in undefined behaviour
		// especially beacause elements in m_enginesVector are not expected to be moved after initEngines()
		// engines are initilaized in the order they are added
		DLL_EXPORT void initEngines();

		// engines are updated in the order they are added
		DLL_EXPORT bool update();
	};
}
