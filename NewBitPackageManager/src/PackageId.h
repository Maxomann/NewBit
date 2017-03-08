#pragma once
#include "stdafx.h"

namespace nb
{
	class LocalId
	{
		std::vector<std::string> m_components;
		std::string m_localStringRepresentation;

	public:
		DLL_EXPORT LocalId( const char* parse );
		DLL_EXPORT LocalId( std::string parse );
		DLL_EXPORT LocalId( std::vector<std::string> components );
		DLL_EXPORT LocalId( const LocalId& id ) = default;
		DLL_EXPORT LocalId( LocalId&& id ) = default;
		DLL_EXPORT LocalId& operator= ( const LocalId& ) = default;

		DLL_EXPORT const std::vector<std::string>& getComponents()const;
		DLL_EXPORT bool containsComponent( const std::string& component )const;

		DLL_EXPORT const std::string& toString()const;

		DLL_EXPORT operator std::string()const;
		DLL_EXPORT bool operator==( const LocalId& rhs )const;
		DLL_EXPORT bool operator==( const std::string& rhs )const;

		DLL_EXPORT static const char SPLIT_CHAR = ':';
	};

	DLL_EXPORT std::ostream& operator<<( std::ostream& os, const LocalId& obj );

	class GlobalId
	{
		std::string m_package;
		std::string m_globalStringRepresentation;

		std::vector<std::string> parseStringToComponentsAndRemovePackage( std::string parse );

	public:
		DLL_EXPORT GlobalId( const char* parse );
		DLL_EXPORT GlobalId( std::string parse );
		DLL_EXPORT GlobalId( std::string package, std::vector<std::string> components );
		DLL_EXPORT GlobalId( std::string package, LocalId localId );
		DLL_EXPORT GlobalId( const GlobalId& id ) = default;
		DLL_EXPORT GlobalId( GlobalId&& id ) = default;
		DLL_EXPORT GlobalId& operator= ( const GlobalId& ) = default;

		const LocalId local;

		DLL_EXPORT const std::string& getPackageName()const;

		DLL_EXPORT const std::string& toString()const;

		DLL_EXPORT operator std::string()const;
		DLL_EXPORT bool operator==( const LocalId& rhs )const;
		DLL_EXPORT bool operator==( const GlobalId& rhs )const;
		DLL_EXPORT bool operator==( const std::string& rhs )const;
	};

	DLL_EXPORT std::ostream& operator<<( std::ostream& os, const GlobalId& obj );
}
