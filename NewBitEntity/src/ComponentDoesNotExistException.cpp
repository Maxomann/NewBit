#include "ComponentDoesNotExistException.h"

nb::entity::exception::ComponentDoesNotExistException::ComponentDoesNotExistException( const std::string & componentTypeName )
	: m_message( "ComponentDoesNotExistException: TypeName: " + componentTypeName )
{}

const char * nb::entity::exception::ComponentDoesNotExistException::what() const
{
	return m_message.c_str();
}