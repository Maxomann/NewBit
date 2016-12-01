#include "SystemManagerAlreadyInitializedException.h"

nb::entity::exception::SystemManagerAlreadyInitializedException::SystemManagerAlreadyInitializedException()
	: std::runtime_error( "SystemManagerAlreadyInitializedException" )
{}