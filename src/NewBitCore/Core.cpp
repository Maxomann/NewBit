#include "Core.h"
using namespace std;
using namespace experimental;

void nb::Core::loadPluginsFromFolder( std::string pathToFolder )
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
			if( !libraryHandle )
			{
				cout << GetLastError() << endl;
				throw std::runtime_error( "libraryHandle is null" );
			}
			auto connectFunctionPtr = GetProcAddress( libraryHandle, "nbConnectCore" );
			if( !connectFunctionPtr )
			{
				cout << GetLastError() << endl;
				throw std::runtime_error( "connectFunctionPtr is null" );
			}
			std::function<connectFunctionSignature> connectFuntion( reinterpret_cast<connectFunctionSignature*>( connectFunctionPtr ) );
			connectFuntion( &m_engines, &m_gameStates );
		}
	}
#else
#error
#endif
}

nb::Core::Core()
	: m_gameStates( m_engines )
{}

void nb::Core::run()
{
	//init
	loadPluginsFromFolder( "./bin" );

	m_engines.initEngines();

	//main loop
	while( m_engines.update() )
	{
		m_gameStates.checkDestroyGameStates();
		m_gameStates.initNewStates();
		m_gameStates.update();
	};

	m_gameStates.destroy_all();
}
