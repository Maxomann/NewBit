#include "Meta.h"
using namespace std;
using namespace nb;
using namespace experimental;

void Meta::loadFromFile(std::string path)
{
	std::ifstream file;
	file.open(path);
	if (!file.is_open())
		return;

	filesystem::path filepath(path);
	m_associatedFilePath = filepath.parent_path().string() + filepath.filename().string() + Meta::EXTENSION;
	std::ifstream associatedFile;
	associatedFile.open(m_associatedFilePath);
	if (!associatedFile.is_open())
		return;

	file >> m_data;

	m_isLoaded = true;
}

bool nb::Meta::isLoaded() const
{
	return m_isLoaded;
}

const json::json& nb::Meta::getData() const
{
	return m_data;
}

std::string nb::Meta::getAssociatedFilePath() const
{
	return m_associatedFilePath;
}
