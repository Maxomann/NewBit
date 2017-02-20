#include "System.h"
using namespace std;
using namespace nb;

nb::System::System( UpdateOrder updateOrder )
	: m_updateOrder( updateOrder )
{
}

UpdateOrder nb::System::getUpdateOrder() const
{
	return m_updateOrder;
}
