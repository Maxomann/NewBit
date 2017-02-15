#include "MetaFile.h"
using namespace std;
using namespace nb;
using namespace experimental;

const std::string MetaFile::EXTENSION = ".meta";
const std::string MetaFile::ATTR_PATH = "path";

void MetaFile::loadFromFile(std::string path)
{
	std::ifstream file;
	file.open(path);
	if (!file.is_open())
		return;
	file >> m_data;

	filesystem::path filepath(path);
	m_id = filepath.filename().string();
	auto parentPath = filepath.parent_path();

	std::string attr_path = m_data[MetaFile::ATTR_PATH];// .get<std::string>();
	if (attr_path != "")
		m_connectedFilePath = parentPath.string() + attr_path;
	else
	{
		// find connected file
		vector<filesystem::directory_entry> possibleConnectedFiles;

		for (auto& el : filesystem::recursive_directory_iterator(parentPath))
			if (el.path().filename() == filepath.filename())
				possibleConnectedFiles.push_back(el);

		// if we cannot determine a single, unique connected file => abort
		if (possibleConnectedFiles.size() != 1)
			throw exception();
		else
			m_connectedFilePath = possibleConnectedFiles.at(0).path().string();
	}

	std::ifstream associatedFile;
	associatedFile.open(m_connectedFilePath);
	if (!associatedFile.is_open())
		return;

	m_isLoaded = true;
}

bool nb::MetaFile::isLoaded() const
{
	return m_isLoaded;
}

const json::json& nb::MetaFile::getData() const
{
	return m_data;
}

std::string nb::MetaFile::getConnectedFilePath() const
{
	return m_connectedFilePath;
}

const std::string& nb::MetaFile::getId() const
{
	return m_id;
}
