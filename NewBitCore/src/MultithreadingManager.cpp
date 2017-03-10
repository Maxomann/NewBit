#include "MultithreadingManager.h"
using namespace std;
using namespace nb;

void MultithreadingManager::tick()
{
	s_executeNextTick.call_and_clear();
}
