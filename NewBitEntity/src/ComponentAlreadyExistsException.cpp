#include "ComponentAlreadyExistsException.h"

nb::entity::exception::ComponentAlreadyExistsException::ComponentAlreadyExistsException( const std::string & componentTypeName )
	: m_message( "ComponentAlreadyExistsException: TypeName: " + componentTypeName )
{}

const char * nb::entity::exception::ComponentAlreadyExistsException::what()const
{
	return m_message.c_str();
}