#include "Core.h"

using namespace std;

int main()
{
	nb::Core core;
#ifndef _DEBUG
	try
	{
#endif
		core.run();
#ifndef _DEBUG
	}
	catch ( exception& e )
	{
		cout << "Error:" << e.what() << endl;
		system( "pause" );
	}
#endif
	return 0;
}