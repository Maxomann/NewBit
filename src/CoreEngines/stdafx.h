#pragma once
#include <NewBitCore/_PluginCreator.h>

#include <nlohmann/json.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <NewBitEntity/NewBitEntity.h>
#include <NewBitPackageManager\PackageManager.h>
#include <NewBitTexturePacker\NewBitTexturePacker.h>

#include <TGUI\TGUI.hpp>
#include <Box2D/Box2D.h>
#include <noise/noise.h>

#include <array>
#include <math.h>
#include <future>
#include <random>
#include <limits>
#include <list>

#define DLL_EXPORT __declspec(dllexport)
