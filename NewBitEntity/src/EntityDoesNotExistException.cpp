#include "EntityDoesNotExistException.h"

const char * nb::entity::exception::EntityDoesNotExistException::what() const
{
	return "EntityDoesNotExistException";
}