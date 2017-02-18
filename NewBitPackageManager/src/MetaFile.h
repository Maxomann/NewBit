#pragma once
#include "stdafx.h"

namespace nb
{
	class MetaFile
	{
		json::json m_data;
		bool m_isLoaded = false;

		std::string m_connectedFilePath;
		std::string m_id;

		std::string generateIdFromPaths( std::string pathToPackage,
										 std::string relativePath );

	public:
		DLL_EXPORT MetaFile() = default;
		// use this overload for virtual meta file
		DLL_EXPORT MetaFile( std::string pathToPackage,
							 std::string relativePath );
		DLL_EXPORT void loadFromFile( std::string pathToPackage, std::string relativePath );
		DLL_EXPORT bool isLoaded()const;

		DLL_EXPORT const json::json& getData()const;
		DLL_EXPORT std::string getConnectedFilePath()const;

		// returns local id (filename)
		DLL_EXPORT const std::string& getId()const;

		DLL_EXPORT static const std::string EXTENSION;

		//---------------------------------------------
		// Possible default attributes in meta file:

		DLL_EXPORT static const std::string ATTR_PATH; //connected file path
	};
}
