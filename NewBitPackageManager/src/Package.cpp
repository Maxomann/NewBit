#include "Package.h"
using namespace std;
using namespace nb;
using namespace experimental;

void nb::Package::loadFromFolder(std::string path)
{
	filesystem::path p(path);
	m_name = p.filename().string();

	for (auto& el : filesystem::recursive_directory_iterator(p))
	{
		auto itpath = el.path();
		if (itpath.extension().string() == MetaFile::EXTENSION)
		{
			MetaFile metaFile;
			metaFile.loadFromFile(itpath.string());

			if (metaFile.isLoaded())
				m_metaFilesByLocalId[itpath.filename().string()] = std::move(metaFile);
			else
				throw std::exception();
		}
	}

	m_isLoaded = true;
}

bool nb::Package::isLoaded() const
{
	return m_isLoaded;
}

std::string nb::Package::getName() const
{
	return m_name;
}

std::string nb::Package::convertLocalToGlobalId(const std::string localId) const
{
	return m_name + ":" + localId;
}

const MetaFile * nb::Package::getMetaFileById(const std::string& localId) const
{
	try {
		return &m_metaFilesByLocalId.at(localId);
	}
	catch (std::exception e) {
		return nullptr;
	}
}
