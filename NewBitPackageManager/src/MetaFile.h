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

	public:
		MetaFile() = default;
		// use this overload for virtual meta file
		MetaFile(std::string filepath);
		void loadFromFile(std::string path);
		bool isLoaded()const;

		const json::json& getData()const;
		std::string getConnectedFilePath()const;

		// returns local id (filename)
		const std::string& getId()const;

		static const std::string EXTENSION;

		// Possible default attributes in meta file:

		static const std::string ATTR_PATH; //connected file path
	};
}
