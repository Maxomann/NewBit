#include "SystemDoesNotExistException.h"

nb::entity::exception::SystemDoesNotExistException::SystemDoesNotExistException( const std::string & systemTypeName )
	:m_message( "SystemDoesNotExistException: TypeName: " + systemTypeName )
{}

const char * nb::entity::exception::SystemDoesNotExistException::what() const
{
	return m_message.c_str();
}