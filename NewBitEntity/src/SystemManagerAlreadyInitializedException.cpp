#include "SystemManagerAlreadyInitializedException.h"

nb::exception::SystemManagerAlreadyInitializedException::SystemManagerAlreadyInitializedException()
	: std::runtime_error( "SystemManagerAlreadyInitializedException" )
{}
