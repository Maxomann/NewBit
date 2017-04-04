#include"PhysicsSystemCallbacks.h"
using namespace std;
using namespace sf;
using namespace nb;

bool PhysicsAABBCallback::ReportFixture( b2Fixture* fixture )
{
	foundBodies.push_back( fixture->GetBody() );
	return true;//keep going to find all fixtures in the query area
}
