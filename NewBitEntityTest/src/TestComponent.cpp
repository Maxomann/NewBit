#include "TestComponent.h"

TestComponent::TestComponent()
	: nb::entity::Component( this )
{}

void TestComponent::init( const nb::entity::Entity & entity )
{
	has_init = true;
}

void TestComponent::destroy( const nb::entity::Entity & entity )
{}