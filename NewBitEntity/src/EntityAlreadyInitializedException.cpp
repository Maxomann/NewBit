#include "EntityAlreadyInitializedException.h"

const char* nb::entity::exception::EntityAlreadyInitializedException::what() const
{
	return "EntityAlreadyInitializedException";
}