#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <array>
#include <memory>
#include <filesystem>
#include <algorithm>
#include <functional>
#include <utility>
#include <typeinfo>
#include <typeindex>

#ifdef _WIN32
#include <windows.h>
#endif

#include <nlohmann/json.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <NewBitEntity/src/NewBitEntity.h>
#include <NewBitSignals\src\Signal.h>

#define DLL_EXPORT __declspec(dllexport)
