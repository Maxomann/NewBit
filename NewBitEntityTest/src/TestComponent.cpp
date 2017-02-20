#include "TestComponent.h"

void TestComponent::init( const nb::Entity & entity )
{
	has_init = true;
}

void TestComponent::destroy( const nb::Entity & entity )
{}
