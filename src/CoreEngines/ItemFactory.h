#pragma once
#include "stdafx.h"
#include "LabeledFactory.h"
#include "Item.h"

namespace nb
{
	class ResourceEngine;

	using ItemFactory = LabeledFactory<std::unique_ptr<Item>, const ResourceEngine&>;
}
