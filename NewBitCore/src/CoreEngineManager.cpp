#include "CoreEngineManager.h"
using namespace std;
using namespace experimental;

namespace nb
{
	void nb::CoreEngineManager::loadFromFolder( std::string pathToFolder )
	{
#ifdef _WIN32
		for( auto& directoryEntry : filesystem::recursive_directory_iterator( pathToFolder ) )
		{
			auto path = directoryEntry.path();
			auto extension = path.extension().string();
			//make extension lowercase
			std::transform( begin( extension ), end( extension ), begin( extension ), ::tolower );
			if( extension == ".dll" )
			{
				HMODULE libraryHandle = LoadLibrary( path.string().c_str() );
				auto connectFunctionPtr = GetProcAddress( libraryHandle, "connect" );
				if( connectFunctionPtr )
				{
					std::function<connectFunctionType> connectFuntion( reinterpret_cast<connectFunctionType*>( connectFunctionPtr ) );
					auto resultVec = connectFuntion();
					for( auto& el : resultVec )
					{
						auto emplaceRetVal = m_engines.emplace( std::make_pair( el->getId(), move( el ) ) );
						if( !emplaceRetVal.second )
							throw exception();
					}
				}
			}
		}
#else
#error
#endif
	}

	CoreEngine * nb::CoreEngineManager::getEngine( const unsigned int id ) const
	{
		return m_engines.at( id ).get();
	}
}