#include "System.h"
using namespace std;
using namespace nb;

nb::System::System( UpdateOrder updateOrder )
	: m_updateOrder( updateOrder )
{
}

void System::linkToWorld( World* world )
{
	r_world = world;
};

World* System::getWorld()const
{
	return r_world;
};

World * nb::System::world() const
{
	return r_world;
}

UpdateOrder nb::System::getUpdateOrder() const
{
	return m_updateOrder;
}
