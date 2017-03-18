#include "CoreEngineManager.h"
using namespace std;
using namespace experimental;

namespace nb
{
	void nb::CoreEngineManager::loadFromFolder( std::string pathToFolder )
	{
#ifdef _WIN32
		for (auto& directoryEntry : filesystem::recursive_directory_iterator( pathToFolder ))
		{
			auto path = directoryEntry.path();
			auto extension = path.extension().string();
			//make extension lowercase
			std::transform( begin( extension ), end( extension ), begin( extension ), ::tolower );
			if (extension == ".dll")
			{
				HMODULE libraryHandle = LoadLibrary( path.string().c_str() );
				auto connectFunctionPtr = GetProcAddress( libraryHandle, "nbConnectCore" );
				if (connectFunctionPtr)
				{
					std::function<connectFunctionSignature> connectFuntion( reinterpret_cast<connectFunctionSignature*>(connectFunctionPtr) );
					connectFuntion( this );
				}
				else
				{
					throw std::runtime_error( "libraryHandle is null" );
				}
			}
		}
#else
#error
#endif
	}

	void nb::CoreEngineManager::initEngines( const CoreRef& core )
	{
		for (auto& el : m_enginesVector)
		{
			el->linkToCore( &core );
			el->init();
		}
	}

	bool nb::CoreEngineManager::update()
	{
		bool continueRunning = true;
		for (auto& el : m_enginesVector)
			if (!el->update())
				continueRunning = false;
		return continueRunning;
	}
}
