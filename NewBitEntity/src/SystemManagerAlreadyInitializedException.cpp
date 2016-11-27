#include "SystemManagerAlreadyInitializedException.h"

const char * nb::entity::exception::SystemManagerAlreadyInitializedException::what() const
{
	return "SystemManagerAlreadyInitializedException";
}