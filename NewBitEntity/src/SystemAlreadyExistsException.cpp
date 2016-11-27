#include "SystemAlreadyExistsException.h"

nb::entity::exception::SystemAlreadyExistsException::SystemAlreadyExistsException( const std::string & systemTypeName )
	: m_message( "SystemAlreadyExistsException: TypeName: " + systemTypeName )
{}

const char * nb::entity::exception::SystemAlreadyExistsException::what() const
{
	return m_message.c_str();
}