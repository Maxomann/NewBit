#include "TestEngine.h"

using namespace std;

nb::TestEngine::TestEngine()
{
	cout << "TestEngine()" << endl;
}

unsigned int nb::TestEngine::getId() const
{
	cout << "getId()" << endl;
	return 0;
}