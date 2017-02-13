#pragma once
#include "stdafx.h"

namespace nb
{
	class Meta
	{
		json::json m_data;
		bool m_isLoaded = false;

		std::string m_associatedFilePath;

	public:
		void loadFromFile(std::string path);
		bool isLoaded()const;

		const json::json& getData()const;
		std::string getAssociatedFilePath()const;

		static const std::string EXTENSION;
	};

	const std::string Meta::EXTENSION = ".meta";
}
