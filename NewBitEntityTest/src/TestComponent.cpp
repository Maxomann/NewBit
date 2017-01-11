#include "TestComponent.h"

TestComponent::TestComponent()
	: nb::Component( this )
{}

void TestComponent::init( const nb::Entity & entity )
{
	has_init = true;
}

void TestComponent::destroy( const nb::Entity & entity )
{}
