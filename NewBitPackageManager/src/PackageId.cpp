#include "PackageId.h"
using namespace std;
using namespace nb;

nb::LocalId::LocalId( const char * parse )
	:LocalId( string( parse ) )
{
}

nb::LocalId::LocalId( std::string parse )
{
	istringstream iss( parse );
	std::string token;
	while (std::getline( iss, token, SPLIT_CHAR )) {
		if (!token.empty())
			m_components.push_back( token );
	}

	m_localStringRepresentation = move( parse );
}

nb::LocalId::LocalId( std::vector<std::string> components )
{
	m_components = move( components );

	for (const auto& el : m_components)
		m_localStringRepresentation += (el + SPLIT_CHAR);
	m_localStringRepresentation.pop_back();
}

const std::vector<std::string>& nb::LocalId::getComponents() const
{
	return m_components;
}

bool nb::LocalId::containsComponent( const std::string & component ) const
{
	return any_of( m_components.begin(),
				   m_components.end(),
				   [&]( const std::string& el ) {
		return el == component;
	} );
}

const std::string & nb::LocalId::toString() const
{
	return m_localStringRepresentation;
}

nb::LocalId::operator std::string()const
{
	return m_localStringRepresentation;
}

bool nb::LocalId::operator==( const LocalId & rhs ) const
{
	return (m_localStringRepresentation == rhs.m_localStringRepresentation);
}

bool nb::LocalId::operator==( const string & rhs ) const
{
	return (m_localStringRepresentation == rhs);
}

std::ostream& nb::operator<<( std::ostream& os, const LocalId& obj )
{
	os << obj.toString();
	return os;
}

std::vector<std::string> nb::GlobalId::parseStringToComponentsAndRemovePackage( std::string parse )
{
	std::vector<std::string> components;

	istringstream iss( parse );
	std::string token;
	while (std::getline( iss, token, LocalId::SPLIT_CHAR )) {
		if (!token.empty())
			components.push_back( token );
	}

	m_package = components.at( 0 );
	components.erase( components.begin() );

	return components;
}

nb::GlobalId::GlobalId( const char * parse )
	:GlobalId( string( parse ) )
{
}

nb::GlobalId::GlobalId( std::string parse )
	: local( parseStringToComponentsAndRemovePackage( move( parse ) ) )
{
	m_globalStringRepresentation = m_package + LocalId::SPLIT_CHAR + local.toString();
}

nb::GlobalId::GlobalId( std::string package, std::vector<std::string> components )
	: local( components )
{
	m_package = move( package );
	m_globalStringRepresentation = m_package + LocalId::SPLIT_CHAR + local.toString();
}

nb::GlobalId::GlobalId( std::string package, LocalId localId )
	: local( move( localId ) )
{
	m_package = move( package );
	m_globalStringRepresentation = m_package + LocalId::SPLIT_CHAR + localId.toString();
}

const std::string & nb::GlobalId::getPackageName() const
{
	return m_package;
}

const std::string & nb::GlobalId::toString() const
{
	return m_globalStringRepresentation;
}

nb::GlobalId::operator std::string()const
{
	return m_globalStringRepresentation;
}

bool nb::GlobalId::operator==( const LocalId & rhs ) const
{
	return false;
}

bool nb::GlobalId::operator==( const GlobalId & rhs ) const
{
	return (m_globalStringRepresentation == rhs.m_globalStringRepresentation);
}

bool nb::GlobalId::operator==( const string & rhs ) const
{
	return (m_globalStringRepresentation == rhs);
}

std::ostream& nb::operator<<( std::ostream& os, const GlobalId& obj )
{
	os << obj.toString();
	return os;
}
