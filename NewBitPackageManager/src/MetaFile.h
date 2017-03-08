#pragma once
#include "stdafx.h"
#include "PackageId.h"

namespace nb
{
	class MetaFile
	{
		json::json m_data;
		bool m_isLoaded = false;

		std::string m_thisFilepath = "-1";
		std::string m_connectedFilePath = "-1";
		LocalId m_id = "-1";

		LocalId generateIdFromPaths( std::string pathToPackage,
									 std::string relativePath );

	public:
		DLL_EXPORT MetaFile() = default;
		// use this overload for virtual meta file
		DLL_EXPORT MetaFile( std::string pathToPackage,
							 std::string relativePath );
		DLL_EXPORT void loadFromFile( std::string pathToPackage,
									  std::string relativePath );
		DLL_EXPORT bool isLoaded()const;
		DLL_EXPORT void saveToFile()const;

		DLL_EXPORT const json::json& getData()const;
		DLL_EXPORT std::string getConnectedFilePath()const;

		// returns local id (folder0:folder1:...:folderN:filename)
		// filename without extension
		DLL_EXPORT const LocalId& getId()const;

		DLL_EXPORT static const std::string EXTENSION;
	};
}
