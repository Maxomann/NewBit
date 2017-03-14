#include "Connection.h"
using namespace std;
using namespace nb;

Connection::Connection( std::weak_ptr<bool> signalTracker )
	: m_trackablePtr( make_shared<bool>( true ) ),
	m_signalTracker( move( signalTracker ) )
{
}

std::weak_ptr<bool> nb::Connection::getTrackablePtr() const
{
	return m_trackablePtr;
}

bool nb::Connection::is_valid() const
{
	return !m_signalTracker.expired();
}
